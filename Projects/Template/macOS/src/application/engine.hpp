#pragma once

#include "application.hpp"
#include <string>

namespace vrm {
    class Engine {
    public:
        Engine();
        void Run();
        ~Engine();
    private:
        std::unique_ptr<Application> ResolveApplication();
    };
}