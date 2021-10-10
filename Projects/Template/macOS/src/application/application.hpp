#pragma once

#include "../project/project.hpp"

namespace vrm {
    class Application {
    public:
        Application() = default;
        virtual ~Application() = default;
        void StartApplication();
        bool RunMainLoop();
        virtual void Render(float counter) = 0;
        WorldRoot* worldRoot;
    };
}