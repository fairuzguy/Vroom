#pragma once

#include "instance.hpp"
#include "../graphics/camera.hpp"

namespace vrm {
    class Workspace : public Instance {
    public:
        Workspace();
        Camera currentCamera;
    private:
        // eventually will add render targets
    };
}