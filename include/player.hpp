/**
 * @file player.hpp
 * @author Lada-Rom, ArtemK
 * @brief Class of main character (playable)
 * @version 0.1
 * @date 2025-01-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef MAGIC_PLAYER_HPP
#define MAGIC_PLAYER_HPP

#include <SDL3/SDL.h>

#include "common/types.hpp"
#include "geometry/vector2d.hpp"

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

    void Move(const Vector2f& rel_move, const real32& time_delta_move) {
        Vector2f norm_delta_move { rel_move.normalize() * time_delta_move };
        //std::cout << "MOVEEE " << norm_delta_move << ' ' << time_delta_move << ' ' << rel_move.normalize() << std::endl;
        real32 norm_x{ norm_delta_move.x() * abs_move };
        real32 norm_y{ norm_delta_move.y() * abs_move };
        
        Move(norm_x, norm_y);
    }

    void Move(real32 delta_x, real32 delta_y) override {
        rect.x += delta_x;
        rect.y += delta_y;
    }

    bool Draw(SDL_Renderer *renderer) override {
        return SDL_RenderFillRect(renderer, &(this->rect));
    }

private:
    const real32 abs_move{ 100.f };
    SDL_FRect rect{ 10.f, 10.f, 100.f, 100.f };

};

#endif  // !MAGIC_PLAYER_HPP
