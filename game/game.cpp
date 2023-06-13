#include <string>
#include <iostream>
#include <memory>

#include <SDL2pp/SDL2pp.hh>
#ifdef _WIN32
  #include <SDL_main.h>
#endif

#include "resource_manager.hpp"
#include "player.hpp"

namespace pp = SDL2pp;

uu::sint32 scrolling_offset_x = 0;
uu::sint32 scrolling_offset_y = 0;
uu::sint32 scrolling_offset_step = 3;

uu::sint8 PollEvent(SDL_Event& event, Player& player) {
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
        scrolling_offset_x -= scrolling_offset_step;
        break;
      case SDLK_LEFT:
        player.SetRunningLeft();
        scrolling_offset_x += scrolling_offset_step;
        break;
      case SDLK_UP:
        player.SetRunningUp();
        scrolling_offset_y += scrolling_offset_step;
        break;
      case SDLK_DOWN:
        player.SetRunningDown();
        scrolling_offset_y -= scrolling_offset_step;
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
  return 1;
}

std::shared_ptr<pp::Renderer> renderer = nullptr;

void infinityBack(ResourceManager<pp::Texture>& _rm) {
    const uu::sint32 img_width (128);
    const uu::sint32 img_height(128);

    const uu::sint32 last_w(renderer->GetOutputWidth() + img_width);
    const uu::sint32 last_h(renderer->GetOutputHeight() + img_height);

    for(uu::sint32 col(-img_width); col < last_w; col += img_width) {
        for(uu::sint32 row(-img_height); row < last_h; row += img_width) {
            if(std::abs(scrolling_offset_x) > img_width)
                scrolling_offset_x = 0;
            if(std::abs(scrolling_offset_y) > img_height)
                scrolling_offset_y = 0;
            renderer->Copy(
              _rm.Get("background"),
              pp::Rect(0, 0, img_width, img_height),
              pp::Rect(row + scrolling_offset_x,
                       col + scrolling_offset_y,
                       img_width,
                       img_height)
            );
        }
    }
}

const uu::uint16 WINDOW_WIDTH  = 480;
const uu::uint16 WINDOW_HEIGHT = 425;

const uu::uint16 SCREEN_ACTIVE_ZONE_WIDTH  = 960;
const uu::uint16 SCREEN_ACTIVE_ZONE_HEIGHT = 850;

int main(int argc, char* args[]) {
    (void)argc;
    (void)args;
try {
  pp::SDL sdl(SDL_INIT_VIDEO);

  pp::Window window("SDL2pp demo",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT,
    SDL_WINDOW_RESIZABLE);

  renderer = std::make_shared<pp::Renderer>(window, -1, SDL_RENDERER_ACCELERATED);
  ResourceManager<pp::Texture> texture_manager(renderer);
  texture_manager.Create("player", "../../data/player.png");
  texture_manager.Create("background", "../../data/background_grass.png");

  SDL_Event event;
  Player player{
    0.5 * renderer->GetOutputWidth(),
    0.5 * renderer->GetOutputHeight() };

  uint32_t prev_ticks = SDL_GetTicks();

  pp::Rect camera = pp::Rect(0, 0, SCREEN_ACTIVE_ZONE_WIDTH, SCREEN_ACTIVE_ZONE_HEIGHT);

  while (true) {
    uu::uint32 frame_ticks = SDL_GetTicks();
    uu::uint32 frame_delta = frame_ticks - prev_ticks;
    prev_ticks = frame_ticks;

    if (!PollEvent(event, player))
      return 0;

    if (player.IsRunningRight())
      player.MoveRight(frame_delta, renderer->GetOutputWidth());
    if (player.IsRunningLeft())
      player.MoveLeft(frame_delta, renderer->GetOutputWidth());
    if (player.IsRunningUp())
      player.MoveUp(frame_delta, renderer->GetOutputHeight());
    if (player.IsRunningDown())
      player.MoveDown(frame_delta, renderer->GetOutputHeight());

    //Center the camera over the dot
    camera.x = (player.x + 7.0)  - WINDOW_WIDTH  / 2;
    camera.y = (player.y + 11.0) - WINDOW_HEIGHT / 2;

    //Keep the camera in bounds
    if(camera.x < 0) camera.x = 0;
    if(camera.y < 0) camera.y = 0;
    if(camera.x > SCREEN_ACTIVE_ZONE_WIDTH - camera.w)
        camera.x = SCREEN_ACTIVE_ZONE_WIDTH - camera.w;
    if(camera.y > SCREEN_ACTIVE_ZONE_HEIGHT - camera.h)
        camera.y = SCREEN_ACTIVE_ZONE_HEIGHT - camera.h;

    renderer->Clear();
    infinityBack(texture_manager);
    renderer->Copy(
      texture_manager.Get("player"),
      pp::Rect(0, 0, 28, 45),
      pp::Rect(camera.x -28.0 + WINDOW_WIDTH / 2, camera.y -45+  WINDOW_HEIGHT / 2, 56, 90)
    );
    renderer->Present();

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
    return 0;
}
