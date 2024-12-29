#ifndef MAGIC_ACTOR_HPP
#define MAGIC_ACTOR_HPP

#include <SDL3/SDL.h>


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
