
/**
 * @file utils.hpp
 * @author ArtemK
 * @brief Some utils functions
 * @version 1.0
 * @date 2025-01-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#define __UTILS_CUSTOM__

#include "types.hpp"

constexpr Radian deg2rad(const Degree& p_angle) {
    constexpr real32 coef(PI / 180.0);
    return Radian(p_angle * coef);
}

constexpr Degree rad2deg(const Radian& p_angle) {
    constexpr real32 coef(180.0 / PI);
    return Degree(p_angle * coef);
}


#endif //!__UTILS_CUSTOM__
