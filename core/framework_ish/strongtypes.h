#ifndef __STRONG_TYPES__
#define __STRONG_TYPES__

#include "specifictypes.h"

#include <utility>
#include <iostream>
#include <type_traits>

namespace user_utils {

namespace detail {
// TODO: maybe just take from here
// https://github.com/joboccara/NamedType
template <class NumT, class Tag>
class NamedType {
public:
    explicit constexpr
    NamedType(const NumT& p_val) noexcept : m_val(p_val) {}
    explicit constexpr
    NamedType(NumT&& p_val) noexcept : m_val(std::move(p_val)) {}

    constexpr
    NamedType(const NamedType& p_val) noexcept : m_val(p_val.get()) {}
    constexpr
    NamedType(NamedType&& p_val) noexcept : m_val(std::move(p_val.get())) {}

    constexpr
    NumT& get() noexcept { return m_val; }
    constexpr
    const NumT& get() const noexcept { return m_val; }

    // Only for arithmetic types
    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType>
    operator+(const NamedType& rhs) const;

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType>
    operator-(const NamedType& rhs) const;

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType>
    operator*(const NumT& rhs) const;


    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType&>
    operator+=(const NamedType& rhs);

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType&>
    operator-=(const NamedType& rhs);

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType&>
    operator*=(const NumT& rhs);


    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType>
    operator-() const;


    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
    operator==(const NamedType& rhs) const;

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
    operator!=(const NamedType& rhs) const;


    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
    operator<(const NamedType& rhs) const;

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
    operator<=(const NamedType& rhs) const;

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
    operator>(const NamedType& rhs) const;

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
    operator>=(const NamedType& rhs) const;

    // prefix https://en.cppreference.com/w/cpp/language/operator_incdec
    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType&>
    operator++();

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType&>
    operator--();
    //postfix https://en.cppreference.com/w/cpp/language/operator_incdec
    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType&>
    operator++(int /*dummy*/);

    constexpr
    typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType&>
    operator--(int /*dummy*/);
    //

private:
    NumT m_val;
};

template <class NumT, class Tag>
std::ostream& operator<<(std::ostream &out, const NamedType<NumT, Tag> &val) {
    out << val.get();
    return out;
}
//std::istream& operator>>(std::istream &in, NamedType &val) {
//    in >> val.get();
//    return in;
//}

// Only for arithmetic types
template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>>
NamedType<NumT, Tag>::operator+(const NamedType& rhs) const {
    auto ret(*this);
    return (ret += rhs);
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>>
NamedType<NumT, Tag>::operator-(const NamedType& rhs) const {
    auto ret(*this);
    return (ret -= rhs);
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>>
NamedType<NumT, Tag>::operator*(const NumT& rhs) const {
    auto ret(*this);
    return (ret *= rhs);
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>&>
NamedType<NumT, Tag>::operator+=(const NamedType& rhs) {
    this->m_val += rhs.m_val;
    return *this;
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>&>
NamedType<NumT, Tag>::operator-=(const NamedType& rhs) {
    this->m_val -= rhs.m_val;
    return *this;
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>&>
NamedType<NumT, Tag>::operator*=(const NumT& rhs) {
    this->m_val *= rhs;
    return *this;
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>>
NamedType<NumT, Tag>::operator-() const {
    return { -(this->m_val) };
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
NamedType<NumT, Tag>::operator==(const NamedType& rhs) const {
    constexpr decltype(rhs.get()) diff(std::abs(this->m_val - rhs.m_val));
    return (diff < precision_rate);
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
NamedType<NumT, Tag>::operator!=(const NamedType& rhs) const {
    return !(*this == rhs);
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
NamedType<NumT, Tag>::operator<(const NamedType& rhs) const {
    return (this->m_val < rhs.m_val);
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
NamedType<NumT, Tag>::operator<=(const NamedType& rhs) const {
    return ( (*this < rhs) || *this == rhs );
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
NamedType<NumT, Tag>::operator>(const NamedType& rhs) const {
    return (this->m_val > rhs.m_val);
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, bool>
NamedType<NumT, Tag>::operator>=(const NamedType& rhs) const {
    return ( (*this > rhs) || *this == rhs );
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>&>
NamedType<NumT, Tag>::operator++() {
    return (++(this->m_val));
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>&>
NamedType<NumT, Tag>::operator--() {
    return (--(this->m_val));
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>&>
NamedType<NumT, Tag>::operator++(int /*dummy*/) {
    return ((this->m_val)++);
}

template <class NumT, class Tag>
constexpr
typename std::enable_if_t<std::is_arithmetic_v<NumT>, NamedType<NumT, Tag>&>
NamedType<NumT, Tag>::operator--(int /*dummy*/) {
    return ((this->m_val)--);
}

} // detail


using Radian = detail::NamedType<real16, struct RadianTag>;
using Degree = detail::NamedType<real16, struct DegreeTag>;

} // user_utils

#endif // !__STRONG_TYPES__
