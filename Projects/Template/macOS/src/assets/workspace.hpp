#pragma once

#include <functional>
#include <map>
#include "instance.hpp"
#include "object.hpp"
#include "../graphics/camera.hpp"

namespace vrm {
    class Workspace : public Instance {
    public:
        Workspace();
        Camera currentCamera;
        std::map<Object*, bool> renderTargets;
    private:
    };
}