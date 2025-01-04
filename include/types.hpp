/**
 * @file types.hpp
 * @author ArtemK
 * @brief Contains pre-defined types and constants for whole system
 * @version 1.0
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __TYPES__
#define __TYPES__

#include <cstdint>
#include <stdexcept>


class NotImplementedException;

// 8 bit
using real8 = NotImplementedException;
using sint8 = int8_t;
using uint8 = uint8_t;

// 16 bit
using real16 = NotImplementedException;
using sint16 = int16_t;
using uint16 = uint16_t;

// 32 bit
using real32 = float;
using sint32 = int32_t;
using uint32 = uint32_t;

// 64 bit
using real64 = double;
using sint64 = int64_t;
using uint64 = uint64_t;


using Radian = real32;
using Degree = real32;


constexpr real32 PRECISION_RATE = 1e-6f;
constexpr real32 PI = 3.14159265358979323846;
constexpr real32 PI_HALF = PI / 2.f;


class NotImplementedException : public std::logic_error {
public:
    NotImplementedException() 
    : std::logic_error{"Not yet implemented"} {}
};

#endif  // !__TYPES__
