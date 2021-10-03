#include "core-sdfs.hpp"

namespace vrm {
    SphereSDF::SphereSDF(glm::vec3 initialPosition, float initialRadius) : 
        position(initialPosition),
        radius(initialRadius) {
    }
    float SphereSDF::GetSignedDistance(glm::vec3 origin) {
        return glm::length(position - origin) - radius;
    }
    void SphereSDF::SetPosition(glm::vec3 newPosition) {
        position = newPosition;
    }
    void SphereSDF::SetRadius(float newRadius) {
        radius = newRadius;
    }

    BoxSDF::BoxSDF(glm::vec3 initialPosition, glm::vec3 initialSize) :
        position(initialPosition),
        size(initialSize) {
    }
    float BoxSDF::GetSignedDistance(glm::vec3 origin) {
        glm::vec3 q = glm::abs(position - origin) - size;
        return glm::length(glm::max(q, glm::vec3(0.0f))) + glm::min(glm::max(q.x, glm::max(q.y, q.z)), 0.0f);
    }
    void BoxSDF::SetPosition(glm::vec3 newPosition) {
        position = newPosition;
    }
    void BoxSDF::SetSize(glm::vec3 newSize) {
        size = newSize;
    }
}