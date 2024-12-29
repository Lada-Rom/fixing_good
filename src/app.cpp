#include <iostream>
#include <SDL3/SDL.h>

#include "vector2d.hpp"
#include "player.hpp"


SDL_AppResult SDL_AppInit(SDL_Window **window, SDL_Renderer **renderer) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Magic I(v)an", 800, 600, 0, window, renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(SDL_Event *event) {
    if(event) {
        switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
            break;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
            case SDLK_ESCAPE:
                return SDL_APP_SUCCESS;
                break;
            default:
                break;
            }
        default:
            break;
        }
    }

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_IteratePhysics(Player& player, const Vector2f& delta_move) {
    player.Move(delta_move);
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


SDL_AppResult SDL_AppIterate(SDL_Renderer *renderer, Player& player, const Vector2f& delta_move) {
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    SDL_IteratePhysics(player, delta_move);
    SDL_IterateRenderer(renderer, player);
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
    SDL_SetRenderVSync(renderer, 1);

    bool running = true;
    SDL_Event *event = new SDL_Event();

    while (running) {
        Vector2f delta_move{};
        while (SDL_PollEvent(event)) {
            SDL_AppResult result = SDL_AppEvent(event);
            if (result == SDL_APP_SUCCESS) {
                running = false;
            }
        }

        const bool *state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_W]) {
            std::cout << "Dir W " << std::endl;
            delta_move.setY(-1);
            //direction = direction | Direction::UP;
        }
        if (state[SDL_SCANCODE_A]) {
            std::cout << "Dir A " << std::endl;
            delta_move.setX(-1);
            //direction = direction | Direction::LEFT;
        }
        if (state[SDL_SCANCODE_S]) {
            std::cout << "Dir S " << std::endl;
            delta_move.setY(1);
            //direction = direction | Direction::DOWN;
        }
        if (state[SDL_SCANCODE_D]) {
            std::cout << "Dir D " << std::endl;
            delta_move.setX(1);
            //direction = direction | Direction::RIGHT;
        }

        SDL_AppResult result = SDL_AppIterate(renderer, player, delta_move);
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

