#include "engine.hpp"
#include "application.hpp"
#include "opengl-application.hpp"
#include "../debug/debug.hpp"
#include "../platform/sdl-wrapper.hpp"
#include <stdexcept>
#include <string>

namespace vrm {
    Engine::Engine() {}
    
    std::unique_ptr<Application> Engine::ResolveApplication() {
        try {
            print("Creating OpenGL Application ...");
            return std::make_unique<OpenGLApplication>();
        } catch (const std::exception &errorMessage) {
            printErr("OpenGL Application failed to initialize. ", errorMessage);
        }
        throw std::runtime_error("No applications are able to run on your environment. Aborting.");
    }

    void Engine::Run() {
        print("Starting Vroom...");
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        print("SDL initialized successfully!");
        ResolveApplication()->StartApplication();
    }

    Engine::~Engine() {
        SDL_Quit();
    }
}