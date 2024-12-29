#ifndef MAGIC_PLAYER_HPP
#define MAGIC_PLAYER_HPP

#include <SDL3/SDL.h>

#include "actor.hpp"
#include "moveable.hpp"
#include "drawable.hpp"


class Player
    : public Actor
    , public Moveable
    , public Drawable {

public:
    Player() {
        SDL_Log("Player is created");
    };

    ~Player() {
        SDL_Log("Player is deleted");
    }

    void Move(const Vector2f& delta_move) {
        Move(delta_move.x(), delta_move.y());
    }

    void Move(float delta_x, float delta_y) override {
        rect.x += delta_x;
        rect.y += delta_y;
    }

    real32 MoveStep() const {
        return move_delta;
    }

    bool Draw(SDL_Renderer *renderer) {
        return SDL_RenderFillRect(renderer, &(this->rect));
    }

private:
    const real32 move_delta{ 3 };
    SDL_FRect rect{ 10.f, 10.f, 100.f, 100.f };

};

#endif  // !MAGIC_PLAYER_HPP
