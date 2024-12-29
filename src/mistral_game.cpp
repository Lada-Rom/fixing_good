#include <SDL3/SDL.h>
#include <iostream>

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Character dimensions
const int CHARACTER_WIDTH = 50;
const int CHARACTER_HEIGHT = 50;

// Function to initialize SDL
bool init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

// Function to load media
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cerr << "Unable to create texture from " << path << "! SDL_Error: " << SDL_GetError() << std::endl;
        }
        SDL_DestroySurface(loadedSurface);
    }
    return newTexture;
}

// Function to close SDL
void close(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        std::cerr << "Failed to initialize!" << std::endl;
    } else {
        SDL_Window* window = SDL_CreateWindow("SDL Character Movement", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if (window == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
            if (renderer == nullptr) {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            } else {
                SDL_Texture* characterTexture = loadTexture("../resources/images/character.bmp", renderer);
                if (characterTexture == nullptr) {
                    std::cerr << "Failed to load character texture!" << std::endl;
                } else {
                    bool quit = false;
                    SDL_Event e;

                    // Character position
                    float xPos = SCREEN_WIDTH / 2;
                    float yPos = SCREEN_HEIGHT / 2;

                    // Character velocity
                    float xVel = 0;
                    float yVel = 0;

                    float denom = 1000.f;

                    while (!quit) {

                        while (SDL_PollEvent(&e) != 0) {
                            if (e.type == SDL_EVENT_QUIT) {
                                quit = true;
                            } else if (e.type == SDL_EVENT_KEY_DOWN && !(e.key.repeat)) {
                                switch (e.key.key) {
                                    case SDLK_UP: yVel -= CHARACTER_HEIGHT / denom; std::cout << "yvel UP (pressed) " << yVel << std::endl; break;
                                    case SDLK_DOWN: yVel += CHARACTER_HEIGHT / denom; break;
                                    case SDLK_LEFT: xVel -= CHARACTER_WIDTH / denom; break;
                                    case SDLK_RIGHT: xVel += CHARACTER_WIDTH / denom; break;
                                }
                            } else if (e.type == SDL_EVENT_KEY_UP) {
                                switch (e.key.key) {
                                    case SDLK_UP: yVel += CHARACTER_HEIGHT / denom; std::cout << "yvel UP (UNpressed) " << yVel << std::endl; break;
                                    case SDLK_DOWN: yVel -= CHARACTER_HEIGHT / denom; break;
                                    case SDLK_LEFT: xVel += CHARACTER_WIDTH / denom; break;
                                    case SDLK_RIGHT: xVel -= CHARACTER_WIDTH / denom; break;
                                }
                            }
                        }

                        // Move the character
                        xPos += xVel;
                        yPos += yVel;

                        // Clear screen
                        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderClear(renderer);

                        // Render character
                        SDL_FRect renderQuad = { float(xPos), float(yPos), CHARACTER_WIDTH, CHARACTER_HEIGHT };
                        SDL_RenderTexture(renderer, characterTexture, NULL, &renderQuad);

                        // Update screen
                        SDL_RenderPresent(renderer);
                    }
                }

                // Free resources and close SDL
                close(window, renderer, characterTexture);
            }
        }
    }

    return 0;
}
