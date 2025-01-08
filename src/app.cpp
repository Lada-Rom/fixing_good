/**
 * @file app.cpp
 * @author Lada-Rom, ArtemK
 * @brief Main point of game
 * @version 0.0.1
 * @date 2025-01-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <SDL3/SDL.h>

#include "player.hpp"
#include "common/types.hpp"
#include "geometry/vector2d.hpp"
#include "timer.hpp"



constexpr real32 TARGET_FPS = 30.f;
constexpr real32 TARGET_TICK_PER_FRAME = 1.0f / TARGET_FPS;

SDL_AppResult SDL_AppInit(SDL_Window **window, SDL_Renderer **renderer) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Magic I(v)an", 800, 600, 0, window, renderer)) {
        SDL_Log("Couldn't create window/renderer: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(SDL_Event *event) {

    if(event) {
        switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
            case SDLK_ESCAPE:
                return SDL_APP_SUCCESS;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_IteratePhysics(Player& player, const Vector2f& delta_move, const real32 timeDelta) {
    //SDL_Log("Time Delta %f", timeDelta);
    //std::cout << "vector " << delta_move << std::endl;
    player.Move(delta_move, timeDelta);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_IterateRenderer(SDL_Renderer* renderer, Player& player) {
    SDL_SetRenderDrawColorFloat(renderer, 0.5, 0.1, 0.7, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColorFloat(renderer, 0.1, 0.1, 0.1, SDL_ALPHA_OPAQUE_FLOAT);
    bool ret = player.Draw(renderer);

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(SDL_Renderer *renderer, Player& player, const Vector2f& delta_move, const real32 deltaTime) {
    //static real32 last = 0.f;
    //static real32 time_delta = 0.f;
    static Timer timer;
    timer.start();

    // Also SDL3 has `SDL_GetTicksNs` - nanoseconds
    //const real32 start = static_cast<real32>(SDL_GetTicks()) * 1e-3f; /* convert from milliseconds to seconds. */

    SDL_IteratePhysics(player, delta_move, deltaTime);
    SDL_IterateRenderer(renderer, player);

    //if (time_delta < TARGET_DELAY) { /* TARGET_DEALY in seconds */
    //    const real32 time_delta_delay = start - static_cast<real32>(SDL_GetTicks()) * 1e-3;
    //    const real32 delayTime(TARGET_DELAY - time_delta_delay);

    //    SDL_Log("Now %f, Delta %f, TDelay %f, Last %f", start, time_delta, TARGET_DELAY, last);
    //    SDL_Delay( static_cast<uint32>(delayTime * 1e3f) );
    //}


    auto value = timer.getElapsedTime() * 1e-9f;
    //SDL_Log("TimeElapsed %f", value);

    //last = static_cast<real32>(SDL_GetTicks()) * 1e-3;
    //time_delta = last - start;

    return SDL_APP_CONTINUE;
}


int main(int /*argc*/, char** /*argv*/) {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    Player player = Player();

    SDL_AppResult result = SDL_AppInit(&window, &renderer);
    if (result == SDL_APP_FAILURE) {
        return EXIT_FAILURE;
    }
    // SDL_SetRenderVSync(renderer, 1);

    bool running = true;
    SDL_Event *event = new SDL_Event();

    Timer fps_timer;
    Timer cap_timer;
    size_t frames_count{0};
    fps_timer.start();
    real32 frame_ticks{};
    while (running) {
        cap_timer.stop();
        cap_timer.reset();
        cap_timer.start();

        Vector2f delta_move{};
        while (SDL_PollEvent(event)) {
            SDL_AppResult result = SDL_AppEvent(event);
            if (result == SDL_APP_SUCCESS) {
                running = false;
            }
        }

        const bool *state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_W]) {
            delta_move.setY(-1.f);
        }
        if (state[SDL_SCANCODE_A]) {
            delta_move.setX(-1.f);
        }
        if (state[SDL_SCANCODE_S]) {
            delta_move.setY(1.f);
        }
        if (state[SDL_SCANCODE_D]) {
            delta_move.setX(1.f);
        }

        real32 time = fps_timer.getElapsedTime() * 1e-9f;
        real32 avg_fps = 1.f * frames_count / time;
        std::cout << "FRAMES " << frames_count << " TIME " << time << " AVG " << avg_fps << std::endl;

        SDL_AppResult result = SDL_AppIterate(renderer, player, delta_move, frame_ticks);

        ++frames_count;
        frame_ticks = cap_timer.getElapsedTime() * 1e-9f;
        //std::cout << "TIME " << frame_ticks << " TICK " << TARGET_TICK_PER_FRAME << std::endl;
        if (frame_ticks < TARGET_TICK_PER_FRAME) {
            SDL_Delay((TARGET_TICK_PER_FRAME - frame_ticks) * 1e3f);
            frame_ticks += (TARGET_TICK_PER_FRAME - frame_ticks) * 1e3f;
        }
    }
    delete event;
    //Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    //Quit SDL subsystems
    SDL_Quit();

    return EXIT_SUCCESS;
}

