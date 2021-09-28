#include "opengl-application.hpp"
#include "../debug/debug.hpp"
#include <string>

namespace vrm {
    SDL_GLContext CreateContext(SDL_Window* window) {
        SDL_GLContext context = SDL_GL_CreateContext(window);
#ifdef WIN32
        glewInit();
#endif
        int viewportWidth;
        int viewportHeight;
        SDL_GL_GetDrawableSize(window, &viewportWidth, &viewportHeight);
        print("Created OpenGL context with viewport size " + std::to_string(viewportWidth) + " x " + std::to_string(viewportHeight) + ".");
        glClearDepthf(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glViewport(0, 0, viewportWidth, viewportHeight);
        return context;
    }

    OpenGLApplication::OpenGLApplication() :
        window(CreateWindow(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)),
        context(CreateContext(window)) {
    }

    OpenGLApplication::~OpenGLApplication() {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
    }

    void OpenGLApplication::Render() {
        SDL_GL_MakeCurrent(window, context);
        glClearColor(0.3f, 0.7f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }
}