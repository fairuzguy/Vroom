#include "core-sdfs.hpp"
#include <functional>

namespace vrm {
    SphereSDF::SphereSDF(glm::vec3 initialPosition, float initialRadius) : 
        radius(initialRadius) {
        this->SetPosition(initialPosition);
        GetSignedDistance = [=](glm::vec3 origin) {
            return this->GetPrimitiveSignedDistance(origin);
        };
    }
    float SphereSDF::GetPrimitiveSignedDistance(glm::vec3 origin) {
        return glm::length(this->GetPosition() - origin) - radius;
    }
    void SphereSDF::SetRadius(float newRadius) {
        radius = newRadius;
    }

    BoxSDF::BoxSDF(glm::vec3 initialPosition, glm::vec3 initialSize) :
        size(initialSize) {
        this->SetPosition(initialPosition);
        GetSignedDistance = [=](glm::vec3 origin) {
            return this->GetPrimitiveSignedDistance(origin);
        };
    }
    float BoxSDF::GetPrimitiveSignedDistance(glm::vec3 origin) {
        glm::vec3 q = glm::abs(this->GetPosition() - origin) - size;
        return glm::length(glm::max(q, glm::vec3(0.0f))) + glm::min(glm::max(q.x, glm::max(q.y, q.z)), 0.0f);
    }
    void BoxSDF::SetSize(glm::vec3 newSize) {
        size = newSize;
    }
}