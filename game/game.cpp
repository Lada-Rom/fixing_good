#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL2pp/Surface.hh>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
//try {
//  if (SDL_Init(SDL_INIT_VIDEO) < 0)
//    throw std::runtime_error("SDL initialization failed");
//
//  Window window("SDL Tutorial",
//    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//  Surface screenSurface = window.GetSurface();
//  screenSurface.FillRect(nullptr, screenSurface.Format(), 225, 255, 128);
//  window.UpdateSurface();
//
//  SDL_Event e;
//  bool quit = false;
//  while (quit == false) {
//    while (SDL_PollEvent(&e)) {
//      if (e.type == SDL_QUIT) quit = true;
//    }
//  }
//
//  SDL_Quit();
//
//  return 0;
//}
//catch (const std::exception& ex) {
//  std::cout << ex.what() << std::endl;
//}
  SDL2pp::Rect rect(0, 0, 12, 24);
  return 0;
}
