#pragma once

#include "service.hpp"
#include "../logic/event.hpp"

namespace vrm {
    class RunServiceContainer : public Service {
    public:
        RunServiceContainer() = default;
        Event<void, float> RenderStepped = Event<void, float>();
        ~RunServiceContainer() = default;
    };
}