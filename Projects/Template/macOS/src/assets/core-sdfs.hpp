#pragma once

#include "sdf.hpp"
#include "../platform/glm-wrapper.hpp"

namespace vrm {
    class SphereSDF : public SDF {
    public:
        SphereSDF(glm::vec3 initialPosition, float initialRadius);
        float GetPrimitiveSignedDistance(glm::vec3 origin);
        void SetRadius(float newRadius);
    private:
        float radius;
    };

    class BoxSDF : public SDF {
    public:
        BoxSDF(glm::vec3 initialPosition, glm::vec3 initialSize);
        float GetPrimitiveSignedDistance(glm::vec3 origin);
        void SetSize(glm::vec3 newSize);
    private:
        glm::vec3 size;
    };
}