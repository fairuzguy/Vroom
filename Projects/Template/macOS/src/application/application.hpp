#pragma once

namespace vrm {
    class Application {
    public:
        Application() = default;
        virtual ~Application() = default;
        void StartApplication();
        bool RunMainLoop();
        virtual void Render() = 0;
    };
}