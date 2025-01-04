// FIXME: 
// For what do we need this class ???
/**
 * @file actor.hpp
 * @author ArtemK
 * @brief Base class for all objects in the scene
 * @version 0.1
 * @date 2025-01-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
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
