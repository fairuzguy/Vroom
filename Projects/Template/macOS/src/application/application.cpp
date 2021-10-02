#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "../platform/sdl-wrapper.hpp"
#include "application.hpp"

namespace vrm {
#ifdef __EMSCRIPTEN__
    void EmscriptenMainLoop(Application* application) {
        application->RunMainLoop();
    }
#endif

    void Application::StartApplication() {
#ifdef __EMSCRIPTEN__
        emscripten_set_main_loop_arg((em_arg_callback_func) EmscriptenMainLoop, this, 60, 1);
#else
        while (RunMainLoop()) {
        }
#endif
    }

    bool Application::RunMainLoop() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Need event callback here for main application

            // Closing events
            switch (event.type) {
                case SDL_QUIT:
                    return false;
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        return false;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        Render();
        return true;
    }
}