#include "app.hpp"

App::App() {
    event = new SDL_Event();
    fps = std::make_unique<FPSControl>(settings);
    SDL_Log("App is created");
}

App::~App() {
    delete event;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_Log("App is deleted");
    SDL_Quit();
}

bool App::IsRunning() {
    return is_running;
}

SDL_AppResult App::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(settings.window_name.c_str(),
        settings.window_width,
        settings.window_height,
        0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult App::ProcessEvent() {
    while (SDL_PollEvent(event)) {
        SDL_AppResult result = AppProcessEvent(event);
        if (result == SDL_APP_SUCCESS) {
            is_running = false;
            return SDL_APP_SUCCESS;
        }
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult App::ProcessState() {
    rel_move = Vector2f();
    const bool* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_W]) {
        rel_move.setY(-1.f);
    }
    if (state[SDL_SCANCODE_A]) {
        rel_move.setX(-1.f);
    }
    if (state[SDL_SCANCODE_S]) {
        rel_move.setY(1.f);
    }
    if (state[SDL_SCANCODE_D]) {
        rel_move.setX(1.f);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult App::AppIteratePhysics() {
    real32 time_delta_move = fps->GetFrameTime();
    player.Move(rel_move, time_delta_move);
    return SDL_APP_CONTINUE;
}

SDL_AppResult App::AppIterateRenderer() {
    SDL_SetRenderDrawColorFloat(renderer, 0.5, 0.1, 0.7, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColorFloat(renderer, 0.1, 0.1, 0.1, SDL_ALPHA_OPAQUE_FLOAT);
    bool ret = player.Draw(renderer);

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}


SDL_AppResult App::AppProcessEvent(SDL_Event* event) {
    if (event) {
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
