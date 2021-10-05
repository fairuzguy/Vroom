// Input data
varying vec4 fragmentColor;
uniform mat4 mvp;
uniform float counter;
uniform vec2 iResolution;

// Object data
uniform mat4 SDFCoreData[100]; // position, orientation, vec4(Refl, Transp, IoR, something else?)
uniform mat4 SDFRenderData[100]; // property data (ex. SphereSDF has radius) plus colour/texture info
uniform vec4 ExpressionList[100]; // first vec4 contains meta data
uniform int SDFList[100]; // list of SDFs to render

// Constants
const int MAX_SDF_COUNT = 100;
const vec3 CLEAR_COLOR = vec3(0.0);
const float EPSILON = 0.0001;
const float TOLERANCE = 0.01;
const float MAX_DISTANCE = 100.0;
const int MAX_STEPS = 100;
const float SHADOW_SURF = 0.02;
const float SOFT_SHADOW_DIST = 0.2;
const float SHADOW_SHARPNESS = 32.0;
const int AO_MAX_STEPS = 5;
const float PI = 3.14159;
const vec2 PARITY_VECTOR = vec2(1.0, -1.0);

// Enums for each primitive
const int ENUM_SDF_SPHERE = 0;
const int ENUM_SDF_BOX = 1;

// Enums for each boolean operation
const int ENUM_OP_UNION = 0;
const int ENUM_OP_SUB = 1;
const int ENUM_OP_INTERSECT = 2;

// Enums for each evaluation mode
const int ENUM_EVAL_NONE = 0;
const int ENUM_EVAL_LEFT = 1;
const int ENUM_EVAL_RIGHT = 2;
const int ENUM_EVAL_BOTH = 3;

// Forward declarations for functions
float GetSignedDistance(vec3 origin);
float RayMarch(vec3 rayOrigin, vec3 rayDirection);
vec3 GetNormal(vec3 origin);
vec2 LightMarch(vec3 rayOrigin, vec3 lightDirection, float lightDist);
float AmbientOcclusion(vec3 rayOrigin, vec3 normal);
float GetLight(vec3 origin);

void main() {
    // Derived values
    vec2 uv = (gl_FragCoord.xy - iResolution.xy*0.5)/iResolution.y;
    vec3 rayPosition = vec3(0.0);//mvp[0].xyz;
    vec3 rightVector = mvp[1].xyz;
    vec3 upVector = mvp[2].xyz;
    vec3 lookVector = mvp[3].xyz;
    float zoom = mvp[0].w;
    vec3 rayDirection = normalize(zoom*lookVector + uv.x*rightVector + uv.y*upVector);

    vec3 color = vec3(
        0.5 + 0.5*sin(uv.x + counter), 
        0.5 + 0.5*sin(uv.y + counter + 2.0*PI/3.0), 
        0.5 + 0.5*sin(uv.x + uv.y + counter + 4.0*PI/3.0)
    );

    gl_FragColor = vec4(color, 1.0);
}

// Distance functions for primitives
float SphereSDF(vec3 origin, vec3 spherePosition, float radius) {
    return length(origin - spherePosition) - radius;
}
float BoxSDF(vec3 origin, vec3 boxPosition, vec3 boxSize) {
    vec3 q = abs(boxPosition - origin) - boxSize;
    return length(max(q, vec3(0.0))) + min(max(q.x, max(q.y, q.z)), 0.0);
}

// Composition functions for boolean operations
float Union(float dist1, float dist2) {
    return min(dist1, dist2);
}
float Sub(float dist1, float dist2) {
    return max(-dist1, dist2);
}
float Intersect(float dist1, float dist2) {
    return max(dist1, dist2);
}

// Global distance function
float GetSignedDistance(vec3 origin) {
    int numSDFs = int(ExpressionList[0].x);
    float evaluatedExpressions[100];
    float minDist = MAX_DISTANCE;
    for (int i = 1; i < MAX_SDF_COUNT; i++) {
        if (i >= numSDFs) {
            break;
        }
        vec4 expression = ExpressionList[i];
        float dist1 = 0.0;
        float dist2 = 0.0;
        int opEnum = int(expression.y);
        int sdfEnum1 = 0;
        int sdfEnum2 = 0;
        mat4 renderData1 = mat4(0.0);
        mat4 renderData2 = mat4(0.0);
        mat4 coreData1 = mat4(0.0);
        mat4 coreData2 = mat4(0.0);
        int sdfIndex1 = int(expression.x);
        int sdfIndex2 = int(expression.z);
        int loopCounter = 0;
        for (int j = 0; j < MAX_SDF_COUNT; j++) { // necessary for OpenGL ES 2.0 ...
            if (j == sdfIndex1) {
                sdfEnum1 = SDFList[j];
                renderData1 = SDFRenderData[j];
                coreData1 = SDFCoreData[j];
                dist1 = evaluatedExpressions[j];
                loopCounter += 1;
            }
            if (j == sdfIndex2) {
                sdfEnum2 = SDFList[j];
                renderData2 = SDFRenderData[j];
                coreData2 = SDFCoreData[j];
                dist2 = evaluatedExpressions[j];
                loopCounter += 1;
            }
            if (loopCounter >= 2) { // cutting the loop as soon as possible
                break;
            }
        }
        vec3 position1 = coreData1[0].xyz;
        vec3 position2 = coreData2[0].xyz;
        if (int(expression.w) == ENUM_EVAL_NONE) { // now we can evaluate without dynamic array access
            if (sdfEnum1 == ENUM_SDF_SPHERE) {
                float radius = renderData1[0].x;
                dist1 = SphereSDF(origin, position1, radius);
            }
            else if (sdfEnum1 == ENUM_SDF_BOX) {
                vec3 size = renderData1[0].xyz;
                dist1 = BoxSDF(origin, position1, size);
            }
            if (sdfEnum2 == ENUM_SDF_SPHERE) {
                float radius = renderData2[0].x;
                dist2 = SphereSDF(origin, position2, radius);
            }
            else if (sdfEnum2 == ENUM_SDF_BOX) {
                vec3 size = renderData2[0].xyz;
                dist2 = BoxSDF(origin, position2, size);
            }
        }
        else if (int(expression.w) == ENUM_EVAL_LEFT) {
            if (sdfEnum2 == ENUM_SDF_SPHERE) {
                float radius = renderData2[0].x;
                dist2 = SphereSDF(origin, position2, radius);
            }
            else if (sdfEnum2 == ENUM_SDF_BOX) {
                vec3 size = renderData2[0].xyz;
                dist2 = BoxSDF(origin, position2, size);
            }
        }
        else if (int(expression.w) == ENUM_EVAL_RIGHT) {
            if (sdfEnum1 == ENUM_SDF_SPHERE) {
                float radius = renderData1[0].x;
                dist1 = SphereSDF(origin, position1, radius);
            }
            else if (sdfEnum1 == ENUM_SDF_BOX) {
                vec3 size = renderData1[0].xyz;
                dist1 = BoxSDF(origin, position1, size);
            }
        } // no need for ENUM_EVAL_BOTH since they are calculated in the above loop

        if (opEnum == ENUM_OP_UNION) {
            minDist = Union(dist1, dist2);
        }
        else if (opEnum == ENUM_OP_SUB) {
            minDist = Sub(dist1, dist2);
        }
        else if (opEnum == ENUM_OP_INTERSECT) {
            minDist = Intersect(dist1, dist2);
        }
        evaluatedExpressions[i] = minDist;
    }
    return minDist;
}

// Raymarching function
float RayMarch(vec3 rayOrigin, vec3 rayDirection) {
    float distTravelled = 0.0;
    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 position = rayOrigin + rayDirection*distTravelled;
        float dist = GetSignedDistance(position);
        distTravelled += dist;
        if (distTravelled > MAX_DISTANCE || dist < TOLERANCE) {
            break;
        }
    }
    return distTravelled;
}

// Approximating the normal
vec3 GetNormal(vec3 origin) {
    return normalize(
        PARITY_VECTOR.xyy*GetSignedDistance(origin + PARITY_VECTOR.xyy*EPSILON) +
        PARITY_VECTOR.yyx*GetSignedDistance(origin + PARITY_VECTOR.yyx*EPSILON) +
        PARITY_VECTOR.yxy*GetSignedDistance(origin + PARITY_VECTOR.yxy*EPSILON) +
        PARITY_VECTOR.xxx*GetSignedDistance(origin + PARITY_VECTOR.xxx*EPSILON)
    );
}

// Backwards march to light sources
vec2 LightMarch(vec3 rayOrigin, vec3 lightDirection, float lightDist) {
    float distTravelled = 0.0;
    float minShadowDist = 1.0;
    float previousDist = 1000000.0;
    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 position = rayOrigin + lightDirection*distTravelled;
        float dist = GetSignedDistance(position);
        distTravelled += dist;

        // check for distance from scene
        if (distTravelled > MAX_DISTANCE) {
            distTravelled = 1000000.0;
            break;
        }
        
        // check if we reached the light source
        if (distTravelled > lightDist - TOLERANCE) {
            distTravelled += TOLERANCE; // adjust to ignore shadow case below
            break;
        }

        // hard shadows
        if (dist < TOLERANCE) {
            break;
        }

        // soft shadows
        float triangulatedDist = dist*dist/(2.0*previousDist);
        float d = sqrt(dist*dist - triangulatedDist*triangulatedDist);
        minShadowDist = min(minShadowDist, SHADOW_SHARPNESS*dist/max(0.0, distTravelled - triangulatedDist));

        previousDist = dist; // keeping track of soft shadows
    }
    return vec2(distTravelled, minShadowDist);
}

// Ambient occlusion
float AmbientOcclusion(vec3 origin, vec3 normal) {
    float distTravelled = 0.0;
    float ao = 0.0;
    float aoStep = 0.5;
    for (int i = 0; i < AO_MAX_STEPS; i++) {
        float dist = GetSignedDistance(origin + distTravelled*normal);
        distTravelled += dist;
        ao += aoStep*dist/clamp(distTravelled, 1.0, 1000000.0);
        aoStep *= 0.5;
    }
    return ao;
}

// Basic lighting
float GetLight(vec3 origin) {
    // Temporary point light
    vec3 lightPos = vec3(10.0, 5.0, 6.0);
    lightPos.xyz += vec3(sin(counter), 3.0*cos(counter), 2.0*cos(counter));
    vec3 lightDirection = normalize(lightPos - origin);
    vec3 normal = GetNormal(origin);
    float diffuse = clamp(dot(normal, lightDirection), 0.0, 1.0);
    float lightDist = length(lightPos - origin);
    float grayscale = diffuse;

    // Applying shadows
    vec2 shadow = LightMarch(origin + normal*SHADOW_SURF*5.0, lightDirection, lightDist);
    if (shadow.x < lightDist) {
        grayscale = shadow.x/lightDist*0.01;
    }
    else {
        grayscale *= shadow.y;
    }

    // Applying ambient occlusion
    float ao = AmbientOcclusion(origin + normal*SHADOW_SURF*5.0, normal);
    grayscale += clamp(ao, 0.0, 1.0-diffuse);

    return grayscale; // will expand to other colours later
}
