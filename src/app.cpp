#include <iostream>
#include <SDL3/SDL.h>
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

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(SDL_Event *event, int *direction) {
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

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}


/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(SDL_Renderer *renderer, Player& player, int direction) {
    // std::cout << SDL_GetTicks() << std::endl;
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    // const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    // const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    // const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    SDL_SetRenderDrawColorFloat(renderer, 0.5, 0.1, 0.7, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */
    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    // player.Move(direction);

    SDL_SetRenderDrawColorFloat(renderer, 0.1, 0.1, 0.1, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */
    bool ret = player.Draw(renderer);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
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
        int direction = 0;
        while (SDL_PollEvent(event)) {
            SDL_AppResult result = SDL_AppEvent(event, &direction);
            if (result == SDL_APP_SUCCESS) {
                running = false;
            }
        }

        const bool *state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_W]) {
            std::cout << "Dir W " << direction << std::endl;
            direction = direction | Direction::UP;
        }
        if (state[SDL_SCANCODE_A]) {
            std::cout << "Dir A " << direction << std::endl;
            direction = direction | Direction::LEFT;
        }
        if (state[SDL_SCANCODE_S]) {
            std::cout << "Dir S " << direction << std::endl;
            direction = direction | Direction::DOWN;
        }
        if (state[SDL_SCANCODE_D]) {
            std::cout << "Dir D " << direction << std::endl;
            direction = direction | Direction::RIGHT;
        }
        
        // std::cout << "Dir " << direction << std::endl;
        SDL_AppResult result = SDL_AppIterate(renderer, player, direction);
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

