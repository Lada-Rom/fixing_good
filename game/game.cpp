#include <string>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>

//#include <SDL.h>

namespace pp = SDL2pp;

int main(int argc, char* args[]) {
try {
  pp::SDL sdl(SDL_INIT_VIDEO);

  pp::Window window("SDL2pp demo",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    640, 480,
    SDL_WINDOW_RESIZABLE);

  pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
  pp::Texture sprites(renderer, "../../data/player.png");

  renderer.Clear();
  renderer.Copy(sprites);
  renderer.Present();

  SDL_Delay(5000);

  return 0;
}
catch (pp::Exception& e) {
  std::cerr << "Error in: " << e.GetSDLFunction() << std::endl;
  std::cerr << "  Reason: " << e.GetSDLError() << std::endl;
}
catch (std::exception& e) {
  std::cerr << e.what() << std::endl;
}
}
