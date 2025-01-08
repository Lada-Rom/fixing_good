/**
 * @file drawable.hpp
 * @author ArtemK
 * @brief Class-behaviour for drawable objects
 * @version 0.1
 * @date 2025-01-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef MAGIC_DRAWABLE_HPP
#define MAGIC_DRAWABLE_HPP

struct SDL_Renderer;

class Drawable {
public:
    virtual ~Drawable() {
        SDL_Log("Drawable object is deleted");
    }

    virtual bool Draw(SDL_Renderer *renderer = nullptr) = 0;
};

#endif  // !MAGIC_DRAWABLE_HPP
