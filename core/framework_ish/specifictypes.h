#ifndef __SPECIFIC_TYPES__
#define __SPECIFIC_TYPES__

#include <cstdint>

namespace {
    // rate for float-point operator== and so on
    constexpr static float precision_rate = 1e-6f;
}

namespace user_utils {

/// COMMON ARITHMETIC TYPES ///
using real8 = float;
using sint8  = int8_t;
using uint8 = uint8_t;

//TODO: https://en.cppreference.com/w/cpp/types/floating-point
using real16 = float;
using sint16  = int16_t;
using uint16 = uint16_t;

using real32 = float;
using sint32  = int32_t;
using uint32 = uint32_t;

using real64 = double;
using sint64  = int64_t;
using uint64 = uint64_t;
/// ----------------------- ///


/// TYPES FOR LOOPS ///
using idx_8  = sint8;
using idx_16 = sint16;
using idx_32 = sint32;
using idx_64 = sint64;

using uidx_8  = uint8;
using uidx_16 = uint16;
using uidx_32 = uint32;
using uidx_64 = uint64;
/// --------------- ///


/// GEOMETRY TYPES ///

/// -------------- ///

} // user_utils


#endif // !__SPECIFIC_TYPES__
