#ifndef MAGIC_PLAYER_HPP
#define MAGIC_PLAYER_HPP

#include <SDL3/SDL.h>

#include "actor.hpp"
#include "drawable.hpp"


class Player 
    : public Actor
    , public Drawable {
public:
    Player() {
        SDL_Log("Player is created");
    };

    ~Player() {
        SDL_Log("Player is deleted");
    }


    bool Draw(SDL_Renderer *renderer) {
        return SDL_RenderFillRect(renderer, &(this->rect));
    }

private:
    const int move_delta{ 3 };
    SDL_FRect rect{ 10.f, 10.f, 100.f, 100.f };

};

#endif  // !MAGIC_PLAYER_HPP
