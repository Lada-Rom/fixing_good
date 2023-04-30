#ifndef __VECTROR_2D__
#define __VECTROR_2D__

#include "specifictypes.h"
#include "strongtypes.h"
#include "commonutils.h"

#include <math.h>
#include <limits>
#include <stdexcept>
#include <iostream>

namespace user_utils {

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
            throw out_of_struct_range();
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
            throw out_of_struct_range();
        }
    }

    constexpr
    NumT& operator[](const std::string_view& p_pos) {
        if(p_pos == "x") return m_x;
        else if (p_pos == "y") return m_y;
        else throw out_of_struct_range();
    }

    constexpr
    const NumT& operator[](const std::string_view& p_pos) const {
        if(p_pos == "x") return m_x;
        else if (p_pos == "y") return m_y;
        else throw out_of_struct_range();
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
    constexpr Vector2D rotate(const Degree& p_angle) const noexcept;
    constexpr Vector2D rotate(const Radian& p_angle) const noexcept;
    constexpr Vector2D& rotate_ip(const Degree& p_angle) noexcept;
    constexpr Vector2D& rotate_ip(const Radian& p_angle) noexcept;

    constexpr Radian angle() const noexcept;
    constexpr Radian angleBetween(const Vector2D& rhs) const noexcept;

public: // main API
    constexpr
    real32 magnitude() const noexcept;
    constexpr
    Vector2D& normalize() const;
    constexpr
    void normalize_ip();

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

public: // specific conversations
    template <class To>
    constexpr
    operator Vector2D<To>() const;

private: // errors block
    struct division_zero_error: public std::exception {
        const char* what() const throw(){
           return " ==> Error: Attempted to divide by Zero.\n" ;
        }
    };

    struct out_of_struct_range: public std::exception {
        const char* what() const throw(){
           return " ==> Error: Out of struct range.\n" ;
        }
    };

private:
    NumT m_x {};
    NumT m_y {};
};

template <class NumT>
std::ostream& operator<<(std::ostream &out, const Vector2D<NumT> &val) {
    out << "Vector2D(" << val.x() << ", " << val.y() << ")";
    return out;
}

// template should be on ome translation unit
// https://stackoverflow.com/a/4015073
template <class NumT>
constexpr
Vector2D<NumT>::Vector2D(const Vector2D& vec) noexcept
    : m_x(vec.m_x)
    , m_y(vec.m_y) {}

template <class NumT>
constexpr
Vector2D<NumT>& Vector2D<NumT>::operator=(const Vector2D& vec) noexcept {
    if(this != &vec) {
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
    if(std::abs(p_val) < precision_rate)
        throw Vector2D::division_zero_error();
    this->m_x /= p_val;
    this->m_y /= p_val;
    return *this;
}

template <class NumT>
constexpr
bool Vector2D<NumT>::operator==(const Vector2D& rhs) const {
    constexpr decltype(rhs.x()) diff_x(std::abs(this->m_x - rhs.m_x));
    constexpr decltype(rhs.y()) diff_y(std::abs(this->m_y - rhs.m_y));
    return (diff_x < precision_rate && diff_y < precision_rate);
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
real32 Vector2D<NumT>::magnitude() const noexcept {
    return sqrt(static_cast<real32>(m_x * m_x + m_y * m_y));
}

template <class NumT>
constexpr
void Vector2D<NumT>::normalize_ip() {
    auto l(this->magnitude());
    if(l > 0.f) {
        (*this) /= l;
    }
}

template <class NumT>
constexpr
Vector2D<NumT>& Vector2D<NumT>::normalize() const {
    auto ret(*this);
    return ret.normalize_ip();
}

template <class NumT>
constexpr
Vector2D<NumT> Vector2D<NumT>::rotate(const Degree& p_angle) const noexcept {
    auto ret(*this);
    return ret.rotate_ip(p_angle);
}

template <class NumT>
constexpr
Vector2D<NumT> Vector2D<NumT>::rotate(const Radian& p_angle) const noexcept {
    auto ret(*this);
    return ret.rotate_ip(p_angle);
}

template <class NumT>
constexpr
Vector2D<NumT>& Vector2D<NumT>::rotate_ip(const Degree& p_angle) noexcept {
    return this->rotate_ip(deg2rad(p_angle));
}

template <class NumT>
constexpr
Vector2D<NumT>& Vector2D<NumT>::rotate_ip(const Radian& p_angle) noexcept {
    auto x_(static_cast<NumT>( std::cos(p_angle.get()) * this->m_x
                             + std::sin(p_angle.get()) * this->m_y ));
    auto y_(static_cast<NumT>(-std::sin(p_angle.get()) * this->m_x
                             + std::cos(p_angle.get()) * this->m_y ));
    this->m_x = x_;
    this->m_y = y_;
    return *this;
}

template <class NumT>
constexpr
Radian Vector2D<NumT>::angle() const noexcept {
    return Radian(std::atan2(this->m_x, this->m_y));
}

template <class NumT>
constexpr
Radian Vector2D<NumT>::angleBetween(const Vector2D& rhs) const noexcept {
    Radian a_diff(this->angle() - rhs.angle());
    Radian half(PI_HALF);
    if(a_diff > half) a_diff -= half;
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
    // maybe fix: no magnitudes
    return ( std::sin(this->angleBetween(rhs).get()) );
}

template <class NumT>
constexpr
bool Vector2D<NumT>::isCollinear(const Vector2D& rhs) const noexcept {
    auto val(std::abs(this->cross(rhs)));
    return (val < precision_rate);
}

template <class NumT>
constexpr
bool Vector2D<NumT>::isOrtho(const Vector2D& rhs) const noexcept {
    auto val(std::abs(this->dot(rhs)));
    return (val < precision_rate);
}
/// -------- ///

/// SPECIFIC CONVERTATIONS ///
template <class NumT>
template <class To>
constexpr
Vector2D<NumT>::operator Vector2D<To>() const {
    return Vector2D<To>(static_cast<To>(this->m_x),
                        static_cast<To>(this->m_y));
}
/// --------------------- ///

/// TYPES ALIASES ///
using Vector2i = Vector2D<int32>;
using Vector2u = Vector2D<uint32>;
using Vector2f = Vector2D<real32>;
/// ------------- ///

} // user_utils


#endif // !__VECTROR_2D__
