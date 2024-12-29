#ifndef MAGIC_ACTOR_HPP
#define MAGIC_ACTOR_HPP

#include <SDL3/SDL.h>

enum Direction {
    UP    = 1<<0,
    LEFT  = 1<<1,
    DOWN  = 1<<2,
    RIGHT = 1<<3,
    NONE
};

class Actor {
public:
    Actor() {
        SDL_Log("Actor is created");
    }

    virtual ~Actor() {
        SDL_Log("Actor is deleted");
    }


};

#endif  // !MAGIC_ACTOR_HPP
