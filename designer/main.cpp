#include <string>
#include <iostream>

#include <SDL.h>

#include "wrappers/surface.hpp"
#include "wrappers/window.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	Window window;
	Surface screenSurface;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	else {
		window.Create("SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window.IsNullptr())
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		else {
			screenSurface = window.GetSurface();
			screenSurface.FillRect(nullptr, screenSurface.Format(), 225, 255, 128);
			window.UpdateSurface();

			SDL_Event e;
			bool quit = false;
			while (quit == false) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) quit = true;
				}
			}
		}
	}

	SDL_Quit();

	return 0;
}
