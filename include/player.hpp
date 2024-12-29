#ifndef MAGIC_PLAYER_HPP
#define MAGIC_PLAYER_HPP

#include "actor.hpp"
#include <SDL3/SDL.h>


class Player : public Actor {
public:
    Player() {
        SDL_Log("Player is created");
    };

    ~Player() {
        SDL_Log("Player is deleted");
    }

    void Move(int direction) {
        if ((direction & Direction::UP) != 0)
            rect.y -= move_delta;
        if ((direction & Direction::LEFT) != 0)
            rect.x -= move_delta;
        if ((direction & Direction::DOWN) != 0)
            rect.y += move_delta;
        if ((direction & Direction::RIGHT) != 0)
            rect.x += move_delta;
    }

    bool Render(SDL_Renderer *renderer) {
        return SDL_RenderFillRect(renderer, &(this->rect));
    }

private:
    const int move_delta{ 3 };
    SDL_FRect rect{ 10.f, 10.f, 100.f, 100.f };

};

#endif  // !MAGIC_PLAYER_HPP
