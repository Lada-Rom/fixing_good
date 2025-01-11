#ifndef MAGIC_APP_HPP
#define MAGIC_APP_HPP

#include <iostream>
#include <sstream>
#include <memory>
#include <SDL3/SDL.h>

#include "common/types.hpp"
#include "geometry/vector2d.hpp"

#include "fps.hpp"
#include "settings.hpp"
#include "player.hpp"


class App {
public:
    App();
    ~App();

    bool IsRunning();

    SDL_AppResult Init();
    SDL_AppResult ProcessEvent();
    SDL_AppResult ProcessState();

    SDL_AppResult AppIteratePhysics();
    SDL_AppResult AppIterateRenderer();

private:
    SDL_AppResult AppProcessEvent(SDL_Event* event);

public:
    std::unique_ptr<FPSControl> fps{ nullptr };

private:
    AppSettings settings{};

    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };
    SDL_Event* event{ nullptr };

    Player player{};
    Vector2f rel_move{};

    bool is_running{ true };
};

#endif  // !MAGIC_APP_HPP
