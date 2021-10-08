#pragma once

#include "instance.hpp"
#include "sdf.hpp"

namespace vrm {
    class Object : public Instance {
    public:
        Object();
        void SetSDF(SDF* newSDF);
        SDF* GetSDF();
        void SetPosition(glm::vec3 newPosition);
        void SetOrientation(glm::mat3x3 newOrientation);
        glm::vec3 GetPosition();
        glm::mat3x3 GetOrientation();
        ~Object() override;
    private:
        SDF* sdf;
        glm::vec3 position;
        glm::mat3x3 orientation;
    };
}