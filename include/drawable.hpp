#ifndef MAGIC_DRAWABLE_HPP
#define MAGIC_DRAWABLE_HPP

struct SDL_Renderer;

class Drawable {
public:
    virtual ~Drawable() {
        SDL_Log("Drawable object is deleted");
    }

    virtual bool Draw(SDL_Renderer *renderer) = 0;
};

#endif  // !MAGIC_DRAWABLE_HPP
