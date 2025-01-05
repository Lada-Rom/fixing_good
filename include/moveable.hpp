/**
 * @file moveable.hpp
 * @author Lada-Rom
 * @brief Class-behaviour for moveable objects
 * @version 0.1
 * @date 2025-01-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef MAGIC_MOVEABLE_HPP
#define MAGIC_MOVEABLE_HPP

#include "common/types.hpp"

class Moveable {
public:
    // TODO: Do we really need an instance of Moveable class
    // Moveable() = default; 
    virtual ~Moveable() {}

    virtual void Move(real32 delta_x, real32 delta_y) = 0;
};

#endif  // !MAGIC_MOVEABLE_HPP
