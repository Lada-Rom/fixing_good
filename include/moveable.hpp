#ifndef MAGIC_MOVEABLE_HPP
#define MAGIC_MOVEABLE_HPP

#include "types.hpp"

class Moveable {
public:
    // TODO: Do we really need an instance of Moveable class
    // Moveable() = default; 
    virtual ~Moveable() {}

    virtual void Move(real32 delta_x, real32 delta_y) = 0;
};

#endif  // !MAGIC_MOVEABLE_HPP
