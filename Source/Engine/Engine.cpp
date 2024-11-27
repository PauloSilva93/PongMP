#define SDL_MAIN_HANDLED

#include "Engine.hpp"
#include <cassert>
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "GLAD/glad.h"

void Engine::Start() {

    const int WIDTH = 800;
    const int HEIGHT = 600;

    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	SDL_Window* window = SDL_CreateWindow("window", WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    assert(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress), "Fail to initialize GLAD");

    SDL_Event evnt;
	
	bool quit = 0;

	while (quit == 0) {

        while (SDL_PollEvent(&evnt)) {
            switch (evnt.type) {
				case SDL_EVENT_QUIT:
                    quit = 1;
					SDL_Quit();
					break;
            }
        }

    }

    std::cout << "Engine Initialized" << std::endl;
};