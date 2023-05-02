#ifndef __COMMON_UTILS__
#define __COMMON_UTILS__

#include "specifictypes.h"
#include "strongtypes.h"

namespace user_utils {

constexpr real32 PI = 3.14159265358979323846;
constexpr real32 PI_HALF = PI * 0.5;

constexpr Radian deg2rad(const Degree& p_angle) {
    constexpr real16 coef(PI / 180.0);
    return Radian(p_angle.get() * coef);
}

constexpr Degree rad2deg(const Radian& p_angle) {
    constexpr real16 coef(180.0 / PI);
    return Degree(p_angle.get() * coef);
}

template<class R, class L>
using MulType = decltype(std::declval<R>() * std::declval<L>());

template<typename R, typename L>
using AddType = decltype(std::declval<R>() + std::declval<L>());


} // user_utils

#endif // !__COMMON_UTILS__
