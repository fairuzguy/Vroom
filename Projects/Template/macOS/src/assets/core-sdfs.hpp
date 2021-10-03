#pragma once

#include "sdf.hpp"
#include "../platform/glm-wrapper.hpp"

namespace vrm {
    class SphereSDF : public SDF {
    public:
        SphereSDF(glm::vec3 initialPosition, float initialRadius);
        float GetSignedDistance(glm::vec3 origin) override;
        void SetPosition(glm::vec3 newPosition);
        void SetRadius(float newRadius);
    private:
        glm::vec3 position;
        float radius;
    };

    class BoxSDF : public SDF {
    public:
        BoxSDF(glm::vec3 initialPosition, glm::vec3 initialSize);
        float GetSignedDistance(glm::vec3 origin) override;
        void SetPosition(glm::vec3 newPosition);
        void SetSize(glm::vec3 newSize);
    private:
        glm::vec3 position;
        glm::vec3 size;
    };
}