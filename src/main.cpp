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

#include "app.hpp"


int main(int /*argc*/, char** /*argv*/) {
    App app{};

    SDL_AppResult init_res = app.Init();
    if (init_res == SDL_APP_FAILURE) {
        return EXIT_FAILURE;
    }

    app.fps->StartGeneralTimer();
    while (app.IsRunning()) {
        app.fps->StartFrameTimer();
        app.ProcessEvent();
        app.ProcessState();

        app.fps->CalcAvgFPS();
        app.AppIteratePhysics();
        app.AppIterateRenderer();
        app.fps->BoundFPS();
    }

    return EXIT_SUCCESS;
}
