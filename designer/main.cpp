#include <string>
#include <iostream>
#include <vector>

#include <SDL.h>

#include "wrappers/surface.hpp"
#include "wrappers/window.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("SDL initialization failed");

  Window window("SDL Tutorial",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  Surface screenSurface = window.GetSurface();
  screenSurface.FillRect(nullptr, screenSurface.Format(), 225, 255, 128);
  window.UpdateSurface();

  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) quit = true;
    }
  }

  SDL_Quit();

  return 0;
}
