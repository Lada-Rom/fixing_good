/**
 * @file vector2d.hpp
 * @author ArtemK
 * @brief Contains Vector2D realization
 * @version 1.0
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __VECTOR_2D__
#define __VECTOR_2D__

#include <math.h>
#include <limits>
#include <stdexcept>
#include <iostream>

#include "types.hpp"

/**
 * @brief Defines a class for 2-dim Vector object
 * 
 * @tparam NumT Type of Vector's fields
 */
template <class NumT>
class Vector2D {
public:
    constexpr
        Vector2D() = default;
    constexpr
        Vector2D(NumT x, NumT y) noexcept
        : m_x(std::move(x))
        , m_y(std::move(y)) {}
    constexpr
        Vector2D(const Vector2D& vec) noexcept;        
    constexpr
        Vector2D& operator=(const Vector2D& vec) noexcept;
    // https://habr.com/ru/articles/164221/
    constexpr
        Vector2D(Vector2D&& vec) noexcept; // w-out noexcept no move semantic by default
    constexpr
        Vector2D& operator=(Vector2D&& vec) noexcept; // w-out noexcept no move semantic by default
    ~Vector2D() = default;

public: // conversions
    // https://www.reddit.com/r/cpp_questions/comments/kd48uw/convert_one_vector_type_to_another/
    template <class NumU>
    constexpr
        explicit Vector2D(const Vector2D<NumU>& vector);

public: // access op-s
    // constexpr implements inline
    constexpr
        NumT x() const noexcept { return m_x; }
    constexpr
        NumT y() const noexcept { return m_y; }

    constexpr
        NumT& operator[](uint8 p_pos) {
        switch (p_pos) {
        case 0:
            return m_x;
        case 1:
            return m_y;
        default:
            throw std::out_of_range(" ==> Error: Out of struct range.\n");
        }
    }

    constexpr
        const NumT& operator[](uint8 p_pos) const {
        switch (p_pos) {
        case 0:
            return m_x;
        case 1:
            return m_y;
        default:
            throw std::out_of_range(" ==> Error: Out of struct range.\n");
        }
    }

    constexpr
        NumT& operator[](const std::string_view& p_pos) {
        if (p_pos == "x") return m_x;
        else if (p_pos == "y") return m_y;
        else throw std::out_of_range(" ==> Error: Out of struct range.\n");
    }

    constexpr
        const NumT& operator[](const std::string_view& p_pos) const {
        if (p_pos == "x") return m_x;
        else if (p_pos == "y") return m_y;
        else throw std::out_of_range(" ==> Error: Out of struct range.\n");
    }

    constexpr
        void setX(NumT p_x) noexcept { m_x = std::move(p_x); }
    constexpr
        void setY(NumT p_y) noexcept { m_y = std::move(p_y); }

public: // arithmetic op-s
    constexpr Vector2D operator+(const Vector2D& rhs) const;
    constexpr Vector2D& operator+=(const Vector2D& rhs);

    constexpr Vector2D operator-(const Vector2D& rhs) const;
    constexpr Vector2D& operator-=(const Vector2D& rhs);

    constexpr Vector2D operator-() const;

    constexpr Vector2D operator*(NumT p_val) const;
    constexpr Vector2D& operator*=(NumT p_val);

    constexpr Vector2D operator/(NumT p_val) const;
    constexpr Vector2D& operator/=(NumT p_val);

    constexpr bool operator==(const Vector2D& rhs) const;
    constexpr bool operator!=(const Vector2D& rhs) const;

public: // actions with angle
    // suffix `ip` means In-Place
    //constexpr Vector2D rotate(const Degree& p_angle) const noexcept;
    constexpr Vector2D rotate(const Radian& p_angle) const noexcept;
    //constexpr Vector2D& rotate_ip(const Degree& p_angle) noexcept;
    constexpr Vector2D& rotate_ip(const Radian& p_angle) noexcept;

    constexpr Radian angle() const noexcept;
    constexpr Radian angleBetween(const Vector2D& rhs) const noexcept;

public: // main API
    constexpr
        real32 magnitude() const noexcept;
    constexpr
        real32 magnitude_square() const noexcept;

    constexpr
        Vector2D normalize() const;
    constexpr
        Vector2D& normalize_ip();

    constexpr
        real32 dot(const Vector2D& rhs) const noexcept;
private:
    // phantom function (for isOrtho only)
    constexpr
        real32 cross(const Vector2D& rhs) const noexcept;
public:
    constexpr
        bool isCollinear(const Vector2D& rhs) const noexcept;
    constexpr
        bool isOrtho(const Vector2D& rhs) const noexcept;

private:
    NumT m_x{};
    NumT m_y{};
};

template <class NumT>
std::ostream& operator<<(std::ostream& out, const Vector2D<NumT>& val) {
    out << "Vector2D(" << val.x() << ", " << val.y() << ")";
    return out;
}

// template should be on one translation unit
// https://stackoverflow.com/a/4015073
template <class NumT>
constexpr
    Vector2D<NumT>::Vector2D(const Vector2D& vec) noexcept
    : m_x(std::move(vec.m_x))
    , m_y(std::move(vec.m_y)) {}

template <class NumT>
constexpr
    Vector2D<NumT>& Vector2D<NumT>::operator=(const Vector2D& vec) noexcept {
    if (this != &vec) {
        this->m_x = vec.m_x;
        this->m_y = vec.m_y;
    }
    return *this;
}

template <class NumT>
constexpr
    Vector2D<NumT>::Vector2D(Vector2D&& vec) noexcept
    : m_x(std::move(vec.m_x))
    , m_y(std::move(vec.m_y)) {}

template <class NumT>
constexpr
    Vector2D<NumT>& Vector2D<NumT>::operator=(Vector2D&& vec) noexcept {
    std::swap(m_x, vec.m_x);
    std::swap(m_y, vec.m_y);
    return *this;
}

/// ARITHMETIC PART ///
template <class NumT>
constexpr
    Vector2D<NumT> Vector2D<NumT>::operator+(const Vector2D& rhs) const {
    auto ret(*this);
    return (ret += rhs);
}

template <class NumT>
constexpr
    Vector2D<NumT>& Vector2D<NumT>::operator+=(const Vector2D& rhs) {
    this->m_x += rhs.m_x;
    this->m_y += rhs.m_y;
    return *this;
}

template <class NumT>
constexpr
    Vector2D<NumT> Vector2D<NumT>::operator-(const Vector2D& rhs) const {
    auto ret(*this);
    return (ret -= rhs);
}

template <class NumT>
constexpr
    Vector2D<NumT>& Vector2D<NumT>::operator-=(const Vector2D& rhs) {
    this->m_x -= rhs.m_x;
    this->m_y -= rhs.m_y;
    return *this;
}

template <class NumT>
constexpr
    Vector2D<NumT> Vector2D<NumT>::operator-() const {
    return Vector2D<NumT>(-(this->m_x), -(this->m_y));
}

template <class NumT>
constexpr
    Vector2D<NumT> Vector2D<NumT>::operator*(NumT p_val) const {
    auto ret(*this);
    return (ret *= p_val);
}

template <class NumT>
constexpr
    Vector2D<NumT>& Vector2D<NumT>::operator*=(NumT p_val) {
    this->m_x *= p_val;
    this->m_y *= p_val;
    return *this;
}

template <class NumT>
constexpr
    Vector2D<NumT> Vector2D<NumT>::operator/(NumT p_val) const {
    auto ret(*this);
    return (ret /= p_val);
}

template <class NumT>
constexpr
    Vector2D<NumT>& Vector2D<NumT>::operator/=(NumT p_val) {
    if (std::abs(p_val) < PRECISION_RATE)
        throw std::overflow_error(" ==> Error: Attempted to divide by Zero.\n");
    this->m_x /= p_val;
    this->m_y /= p_val;
    return *this;
}

template <class NumT>
constexpr
    bool Vector2D<NumT>::operator==(const Vector2D& rhs) const {
    using type_x = decltype(rhs.x());
    const type_x diff_x(std::abs(this->m_x - rhs.m_x));
    const type_x diff_y(std::abs(this->m_y - rhs.m_y));
    return (diff_x < PRECISION_RATE && diff_y < PRECISION_RATE);
}

template <class NumT>
constexpr
    bool Vector2D<NumT>::operator!=(const Vector2D& rhs) const {
    return !(*this == rhs);
}
/// --------------- ///

/// Main API //
template <class NumT>
constexpr
    real32 Vector2D<NumT>::magnitude_square() const noexcept {
    return static_cast<real32>(m_x * m_x + m_y * m_y);
}

template <class NumT>
constexpr
    real32 Vector2D<NumT>::magnitude() const noexcept {
    return sqrt(this->magnitude_square());
}

template <class NumT>
constexpr
    Vector2D<NumT>& Vector2D<NumT>::normalize_ip() {
    auto l(this->magnitude());
    if (l > PRECISION_RATE) {  /* Do not compare with just 0.f */
        (*this) /= l;
    }
    return *this;
}

template <class NumT>
constexpr
    Vector2D<NumT> Vector2D<NumT>::normalize() const {
    auto ret(*this);
    ret.normalize_ip();
    return ret;
}

//template <class NumT>
//constexpr
//    Vector2D<NumT> Vector2D<NumT>::rotate(const Degree& p_angle) const noexcept {
//    auto ret(*this);
//    return ret.rotate_ip(p_angle);
//}

template <class NumT>
constexpr
    Vector2D<NumT> Vector2D<NumT>::rotate(const Radian& p_angle) const noexcept {
    auto ret(*this);
    return ret.rotate_ip(p_angle);
}

//template <class NumT>
//constexpr
//    Vector2D<NumT>& Vector2D<NumT>::rotate_ip(const Degree& p_angle) noexcept {
//    return this->rotate_ip(deg2rad(p_angle));
//}

template <class NumT>
constexpr
    Vector2D<NumT>& Vector2D<NumT>::rotate_ip(const Radian& p_angle) noexcept {
    const auto x_(static_cast<NumT>(std::cos(p_angle) * this->m_x
        + std::sin(p_angle) * this->m_y));
    const auto y_(static_cast<NumT>(-std::sin(p_angle) * this->m_x
        + std::cos(p_angle) * this->m_y));
    
    this->m_x = x_;
    this->m_y = y_;

    return *this;
}

template <class NumT>
constexpr
    Radian Vector2D<NumT>::angle() const noexcept {
    return Radian(std::atan2(this->m_y, this->m_x));
}

template <class NumT>
constexpr
    Radian Vector2D<NumT>::angleBetween(const Vector2D& rhs) const noexcept {
    if (this->magnitude_square() < PRECISION_RATE 
       || rhs.magnitude_square() < PRECISION_RATE) {
        return static_cast<Radian>(0.f);
    }

    const auto lhs_angle(this->angle());
    const auto rhs_angle(rhs.angle());
    Radian a_diff( std::abs(lhs_angle - rhs_angle) );
    return a_diff;
}

template <class NumT>
constexpr
    real32 Vector2D<NumT>::dot(const Vector2D& rhs) const noexcept {
    return (this->m_x * rhs.m_x + this->m_y * rhs.m_y);
}

template <class NumT>
constexpr
    real32 Vector2D<NumT>::cross(const Vector2D& rhs) const noexcept {
    return (std::sin(this->angleBetween(rhs)));
}

template <class NumT>
constexpr
    bool Vector2D<NumT>::isCollinear(const Vector2D& rhs) const noexcept {
    auto val(std::abs(this->cross(rhs)));
    return (val < PRECISION_RATE);
}

template <class NumT>
constexpr
    bool Vector2D<NumT>::isOrtho(const Vector2D& rhs) const noexcept {
    auto val(std::abs(this->dot(rhs)));
    return (val < PRECISION_RATE);
}
/// -------- ///
template <class NumT>
template <class NumU>
constexpr Vector2D<NumT>::Vector2D(const Vector2D<NumU>& vector) {
    this->m_x = static_cast<NumT>( std::move(vector.x()) );
    this->m_y = static_cast<NumT>( std::move(vector.y()) );
}

/// TYPES ALIASES ///
using Vector2i = Vector2D<sint32>;
using Vector2u = NotImplementedException;
using Vector2f = Vector2D<real32>;
/// ------------- ///


#endif // !__VECTOR_2D__
