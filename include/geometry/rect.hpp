/**
 * @file rect.hpp
 * @author ArtemK
 * @brief Contains Rect realization
 * @version 0.1
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __RECT_2D__
#define __RECT_2D__

#include <optional>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "common/types.hpp"
#include "vector2d.hpp"

/**
 * @brief Defines a class for Rectangle object
 * 
 * @tparam NumT Type of Rectangle's fields
 */
template <class NumT>
class Rect {
public:
    constexpr
        Rect() = default;
    constexpr
        Rect(NumT x, NumT y, NumT width, NumT height) noexcept
        : m_x(std::move(x))
        , m_y(std::move(y))
        , m_width(std::move(width))
        , m_height(std::move(height)) {}
    
    constexpr
        Rect(const Vector2D<NumT>& lt, const Vector2D<NumT>& size) noexcept
        : Rect(lt.x(), lt.y(), size.x(), size.y()) {}

    constexpr
        Rect(NumT x, NumT y, const Vector2D<NumT>& size) noexcept
        : Rect(x, y, size.x(), size.y()) {}

    constexpr
        Rect(const Rect& rect) noexcept
        : Rect(rect.m_x, rect.m_y, rect.m_width, rect.m_height) {}
    constexpr
        Rect& operator=(const Rect& rect) noexcept;
    
    constexpr
        Rect(Rect&& rect) noexcept
        : Rect(rect.m_x, rect.m_y, rect.m_width, rect.m_height) {};
    constexpr
        Rect& operator=(Rect&& rect) noexcept;
    ~Rect() = default;

public:
    constexpr
        NumT x() const noexcept { return m_x; }
    constexpr
        NumT y() const noexcept { return m_y; }
    constexpr
        NumT width() const noexcept { return m_width; }
    constexpr
        NumT height() const noexcept { return m_height; }

    constexpr
        void setX(NumT p_x) noexcept { m_x = std::move(p_x); }
    constexpr
        void setY(NumT p_y) noexcept { m_y = std::move(p_y); }
    constexpr
        void setWidth(NumT p_width) noexcept { m_width = std::move(p_width); }
    constexpr
        void setHeight(NumT p_height) noexcept { m_height = std::move(p_height); }

    constexpr
        void setLeftTop(NumT p_x, NumT p_y) noexcept { 
            setX(p_x);
            setY(p_y);
        }
    constexpr
        void setSize(NumT p_width, NumT p_height) noexcept { 
            setWidth (p_width);
            setHeight(p_height);
        }

public:
    constexpr
        Vector2D<NumT> leftTop() const noexcept { return Vector2D<NumT>(m_x, m_y); }
    constexpr
        Vector2D<NumT> size() const noexcept { return Vector2D<NumT>(m_width, m_height); }
    
    constexpr
        void setLeftTop(const Vector2D<NumT>& lt_pos) {
            setLeftTop(lt_pos.x(), lt_pos.y());
        }
    constexpr
        void setSize(const Vector2D<NumT>& size) {
            setSize(size.x(), size.y());
        }

public:
    constexpr bool operator==(const Rect<NumT>& rhs) const;
    constexpr bool operator!=(const Rect<NumT>& rhs) const;

public:
    constexpr bool contains(NumT x, NumT y) const;
    constexpr bool contains(const Vector2D<NumT>& point) const;
    
    constexpr std::optional<Rect<NumT>> intersects(const Rect<NumT>& rect) const;
    constexpr Rect<NumT> min_union(const Rect<NumT>& rect) const;

    constexpr Vector2D<NumT> getCenter() const;

private:
    NumT m_x{};
    NumT m_y{};
    NumT m_width{};
    NumT m_height{};
};

template <class NumT>
std::ostream& operator<<(std::ostream& out, const Rect<NumT>& val) {
    out << "Rect(" << val.x() << ", " 
                   << val.y() << ", " 
                   << val.width() << ", " 
                   << val.height() << ")";
    return out;
}

template <class NumT>
constexpr
    Rect<NumT>& Rect<NumT>::operator=(const Rect& rect) noexcept {
    if (this != &rect) {
        this->m_x = rect.m_x;
        this->m_y = rect.m_y;
        this->m_width  = rect.m_width;
        this->m_height = rect.m_height;
    }
    return *this;
}

template <class NumT>
constexpr
    Rect<NumT>& Rect<NumT>::operator=(Rect&& rect) noexcept {
    std::swap(m_x, rect.m_x);
    std::swap(m_y, rect.m_y);
    std::swap(m_width , rect.m_width);
    std::swap(m_height, rect.m_height);
    return *this;
}


template <class NumT>
constexpr 
    bool Rect<NumT>::operator==(const Rect<NumT>& rhs) const {
    using type_x = decltype(rhs.x());
    const type_x diff_x(std::abs(this->m_x - rhs.m_x));
    const type_x diff_y(std::abs(this->m_y - rhs.m_y));

    const type_x diff_w(std::abs(this->m_width  - rhs.m_width));
    const type_x diff_h(std::abs(this->m_height - rhs.m_height));

    return (diff_x < PRECISION_RATE && diff_y < PRECISION_RATE 
         && diff_w < PRECISION_RATE && diff_h < PRECISION_RATE);

}

template <class NumT>
constexpr 
    bool Rect<NumT>::operator!=(const Rect<NumT>& rhs) const {
        return !(*this == rhs);
}

// thanx to https://github.com/SFML/SFML/blob/master/include/SFML/Graphics/Rect.inl
template <class NumT>
constexpr 
    bool Rect<NumT>::contains(NumT x, NumT y) const {
    using type_x = decltype(x);

    const type_x x0(this->m_x);
    const type_x y0(this->m_y);
    const type_x x1(this->m_x + this->m_width);
    const type_x y1(this->m_y + this->m_height);

    constexpr type_x lt_x(std::min(x0, x1));
    constexpr type_x lt_y(std::min(y0, y1));

    constexpr type_x rb_x(std::max(x0, x1));
    constexpr type_x rb_y(std::max(y0, y1));

    return (x >= lt_x) && (x < rb_x) 
        && (y >= lt_y) && (y < rb_y);
}

template <class NumT>
constexpr 
    bool Rect<NumT>::contains(const Vector2D<NumT>& point) const {
    return this->contains(point.x(), point.y());
}

// thanx to https://github.com/SFML/SFML/blob/master/include/SFML/Graphics/Rect.inl
template <class NumT>
constexpr 
    std::optional<Rect<NumT>> Rect<NumT>::intersects(const Rect<NumT>& rect) const {
    using type_x = decltype(rect.x());

    const type_x lhs_x0(this->m_x);
    const type_x lhs_y0(this->m_y);
    const type_x lhs_x1(this->m_x + this->m_width);
    const type_x lhs_y1(this->m_y + this->m_height);

    const type_x rhs_x0(rect.m_x);
    const type_x rhs_y0(rect.m_y);
    const type_x rhs_x1(rect.m_x + rect.m_width);
    const type_x rhs_y1(rect.m_y + rect.m_height);

    const type_x lt_x = std::max(lhs_x0, rhs_x0);
    const type_x lt_y = std::max(lhs_y0, rhs_y0);
    const type_x rb_x = std::min(lhs_x1, rhs_x1);
    const type_x rb_y = std::min(lhs_y1, rhs_y1);

    if( (lt_x < rb_x) && (lt_y < rb_y) ) {
        return Rect<NumT>(lt_x, lt_y, rb_x, rb_y);
    }

    return std::nullopt;
}

template <class NumT>
constexpr
    Rect<NumT> Rect<NumT>::min_union(const Rect<NumT>& rect) const {
    using type_x = decltype(rect.x());

    const type_x lhs_x0(this->m_x);
    const type_x lhs_y0(this->m_y);
    const type_x lhs_x1(this->m_x + this->m_width);
    const type_x lhs_y1(this->m_y + this->m_height);

    const type_x rhs_x0(rect.m_x);
    const type_x rhs_y0(rect.m_y);
    const type_x rhs_x1(rect.m_x + rect.m_width);
    const type_x rhs_y1(rect.m_y + rect.m_height);

    const type_x lt_x = std::min(lhs_x0, rhs_x0);
    const type_x lt_y = std::min(lhs_y0, rhs_y0);
    const type_x rb_x = std::max(lhs_x1, rhs_x1);
    const type_x rb_y = std::max(lhs_y1, rhs_y1);

    return Rect<NumT>(lt_x, lt_y, rb_x, rb_y);
}

template <class NumT>
constexpr 
    Vector2D<NumT> Rect<NumT>::getCenter() const {
    return Vector2D<NumT>(this->m_x + static_cast<NumT>(0.5f * this->m_width),
                          this->m_y + static_cast<NumT>(0.5f * this->m_height));
}

/// TYPES ALIASES ///
using IRect = Rect<sint32>;
using FRect = Rect<real32>;
/// ------------- ///


#endif  // !__RECT_2D__
