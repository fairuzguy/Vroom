#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "platform/graphics-wrapper.hpp"
#include "platform/sdl-wrapper.hpp"
#include <iostream>

SDL_Window* window;
SDL_GLContext context;

void Render() {
	SDL_GL_MakeCurrent(window, context);
	glClearColor(0.3f, 0.7f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(window);
}

bool RunMainLoop() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					return false;
				}
				break;
			default:
				break;
		}
	}
	Render();
	return true;
}

#ifdef __EMSCRIPTEN__
void RunEmscriptenMainLoop() {
	RunMainLoop();
}
#endif

void RunApplication() {
	std::pair<uint32_t, uint32_t> displaySize = vrm::GetDisplaySize();
	std::cout << "Display size is: " << displaySize.first << " x " << displaySize.second << std::endl;
	window = vrm::CreateWindow(SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
	context = SDL_GL_CreateContext(window);

#ifdef WIN32
	glewInit();
#endif
	
	glClearDepthf(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glViewport(0, 0, displaySize.first, displaySize.second);

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(RunEmscriptenMainLoop, 60, 1);
#else
	while (RunMainLoop()) {
		// main loop is running here
	}
#endif

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

int main(int, char* []) {
	std::cout << "Initializing SDL ..." << std::endl;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0) {
		std::cout << "Successfully initialized SDL!" << std::endl;
		RunApplication();
		SDL_Quit();
	} else {
		std::cout << "Failed to initialize SDL!" << std::endl;
	}

	return 0;
}
