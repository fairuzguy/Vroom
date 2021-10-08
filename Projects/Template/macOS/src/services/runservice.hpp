#pragma once

#include "../logic/event.hpp"

namespace vrm {
    class RunService {
    public:
        RunService() = default;
        Event<void, float> RenderStepped;
        ~RunService() = default;
    };
}