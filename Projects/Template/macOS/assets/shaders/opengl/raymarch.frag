// Input data
varying vec4 fragmentColor;
uniform mat4 mvp;
uniform float counter;
uniform vec2 iResolution;

// Constants
const vec3 CLEAR_COLOR = vec3(0.0);
const float EPSILON = 0.0001;
const float TOLERANCE = 0.01;
const float MAX_DISTANCE = 100.0;
const int MAX_STEPS = 100;
const float SHADOW_SURF = 0.02;
const float SOFT_SHADOW_DIST = 0.2;
const int AO_MAX_STEPS = 5;

// Forward declarations for functions

void main() {
    // Derived values
    vec2 uv = (gl_FragCoord.xy - iResolution.xy*0.5)/iResolution.y;
    vec3 color = vec3(sin(uv.x*counter), cos(uv.y/counter), tan(uv.x/uv.y + counter));

    gl_FragColor = vec4(color, 0.0);
}