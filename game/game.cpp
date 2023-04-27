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

  bool is_running = false;        // whether the character is currently running
  bool is_running_right = false;  // whether the character is currently running right
  int run_phase = -1;             // run animation phase
  float position = 0.0;           // player position

  unsigned int prev_ticks = SDL_GetTicks();
  while (true) {
    unsigned int frame_ticks = SDL_GetTicks();
    unsigned int frame_delta = frame_ticks - prev_ticks;
    prev_ticks = frame_ticks;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return 0;
      }
      else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
          return 0;

        case SDLK_RIGHT:
          is_running = true;
          is_running_right = true;
          break;
        case SDLK_LEFT:
          is_running = true;
          is_running_right = false;
          break;
        }
      }
      else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_RIGHT:
          is_running = false;
          is_running_right = false;
          break;
        case SDLK_LEFT:
          is_running = false;
          is_running_right = false;
          break;
        }
      }
    }

    if (is_running) {
      if (is_running_right) {
        position += frame_delta * 0.2;
        run_phase = (frame_ticks / 100) % 8;
      }
      if (!is_running_right) {
        position -= frame_delta * 0.2;
        run_phase = (frame_ticks / 100) % 8;
      }
    }
    else {
      run_phase = 0;
    }

    if (position > renderer.GetOutputWidth()) {
      position = -50;
    }
    if (position < -50) {
      position = renderer.GetOutputWidth();
    }
    std::cout << position << std::endl;

    int vcenter = renderer.GetOutputHeight() / 2;
    renderer.Clear();
    renderer.Copy(
      sprites,
      pp::Rect(0, 0, 28, 45),
      pp::Rect((int)position, vcenter - 50, 50, 50)
    );
    renderer.Present();

    SDL_Delay(1);
  }

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
