#pragma once

#include "../platform/glm-wrapper.hpp"
#include "../platform/glm-wrapper.hpp"
#include <vector>

namespace vrm {
    class SDF {
    public:
        SDF();
        SDF(SDF* oldSDFs);
        ~SDF();
        std::function<float(glm::vec3)> GetSignedDistance;
        SDF Union(SDF* sdf);
        SDF Sub(SDF* sdf);
        SDF Intersect(SDF* sdf);
        void SetPosition(glm::vec3 newPosition);
        void SetOrientation(glm::mat3x3 newOrientation);
        glm::vec3 GetPosition();
        glm::mat3x3 GetOrientation();
        SDF* UndoPrevious();
        bool IsPrimitive();
    private:
        SDF* previousComposition = nullptr;
        glm::vec3 position;
        glm::mat3x3 orientation;
        bool isPrimitive = true;
        std::vector<glm::vec3> positionOffsets;
        std::vector<glm::mat3x3> orientationOffsets;
        std::vector<SDF*> sdfList;
    };
}