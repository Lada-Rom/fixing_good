#include <string>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>
#ifdef _WIN32
  #include <SDL_main.h>
#endif

namespace pp = SDL2pp;


struct Player {
  void SetRunningRight() {
    direction[RIGHT] = true;
  }

  void SetRunningLeft() {
    direction[LEFT] = true;
  }

  void SetRunningUp() {
    direction[UP] = true;
  }

  void SetRunningDown() {
    direction[DOWN] = true;
  }

  bool IsRunningRight() {
    return direction[RIGHT];
  }

  bool IsRunningLeft() {
    return direction[LEFT];
  }

  bool IsRunningUp() {
    return direction[UP];
  }

  bool IsRunningDown() {
    return direction[DOWN];
  }

  void StopRunningRight() {
    direction[RIGHT] = false;
  }

  void StopRunningLeft() {
    direction[LEFT] = false;
  }

  void StopRunningUp() {
    direction[UP] = false;
  }

  void StopRunningDown() {
    direction[DOWN] = false;
  }

  void MoveRight(
    const uint32_t& frame_delta,
    const float& max_width) {
    x += frame_delta * 0.2;
    if (x > max_width)
      x = -50;
  }

  void MoveLeft(
    const uint32_t& frame_delta,
    const float& max_width) {
    x -= frame_delta * 0.2;
    if (x < -50)
      x = max_width;
  }

  void MoveUp(
    const uint32_t& frame_delta,
    const float& max_height) {
    y -= frame_delta * 0.2;
    if (y < -50)
      y = max_height;
  }

  void MoveDown(
    const uint32_t& frame_delta,
    const float& max_height) {
    y += frame_delta * 0.2;
    if (y > max_height)
      y = -50;
  }

  float x{};
  float y{};

  enum Running { RIGHT, LEFT, UP, DOWN};
  std::vector<bool> direction{ false, false, false, false };
};


int main(int argc, char* args[]) {
try {
  pp::SDL sdl(SDL_INIT_VIDEO);

  pp::Window window("SDL2pp demo",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    640, 480,
    SDL_WINDOW_RESIZABLE);

  pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
  pp::Texture sprites(renderer, "../../data/player.png");
  Player player{
    0.5 * renderer.GetOutputWidth(),
    0.5 * renderer.GetOutputHeight() };

  uint32_t prev_ticks = SDL_GetTicks();
  while (true) {
    uint32_t frame_ticks = SDL_GetTicks();
    uint32_t frame_delta = frame_ticks - prev_ticks;
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
          player.SetRunningRight();
          break;
        case SDLK_LEFT:
          player.SetRunningLeft();
          break;
        case SDLK_UP:
          player.SetRunningUp();
          break;
        case SDLK_DOWN:
          player.SetRunningDown();
          break;
        }
      }
      else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_RIGHT:
          player.StopRunningRight();
          break;
        case SDLK_LEFT:
          player.StopRunningLeft();
          break;
        case SDLK_UP:
          player.StopRunningUp();
          break;
        case SDLK_DOWN:
          player.StopRunningDown();
          break;
        }
      }
    }

    if (player.IsRunningRight())
      player.MoveRight(frame_delta, renderer.GetOutputWidth());
    if (player.IsRunningLeft())
      player.MoveLeft(frame_delta, renderer.GetOutputWidth());
    if (player.IsRunningUp())
      player.MoveUp(frame_delta, renderer.GetOutputHeight());
    if (player.IsRunningDown())
      player.MoveDown(frame_delta, renderer.GetOutputHeight());

    renderer.Clear();
    renderer.Copy(
      sprites,
      pp::Rect(0, 0, 28, 45),
      pp::Rect(player.x - 14, player.y - 22, 50, 50)
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
