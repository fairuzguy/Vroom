#pragma once

#include "application.hpp"
#include "../platform/graphics-wrapper.hpp"
#include "../platform/sdl-wrapper.hpp"

namespace vrm {
    class OpenGLApplication : public Application {
    public:
        OpenGLApplication();
        void Render() override;
        ~OpenGLApplication();
    private:
        SDL_Window* window;
        SDL_GLContext context;
    };
}