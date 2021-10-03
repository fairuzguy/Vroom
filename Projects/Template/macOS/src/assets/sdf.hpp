#pragma once

#include "../platform/glm-wrapper.hpp"

namespace vrm {
    class SDF {
    public:
        SDF() = default;
        virtual float GetSignedDistance(glm::vec3 origin);
        virtual SDF* Union(SDF* sdf1, SDF* sdf2);
        ~SDF() = default;
    };
}