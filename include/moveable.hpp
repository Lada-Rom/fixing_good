#ifndef MAGIC_MOVEABLE_HPP
#define MAGIC_MOVEABLE_HPP

class Moveable {
public:
    Moveable() = default;
    ~Moveable() = default;

    virtual void Move(float delta_x, float delta_y) = 0;
};

#endif  // !MAGIC_MOVEABLE_HPP
