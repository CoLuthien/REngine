
#pragma once

#include "core_export.hpp"

#include <cstdint>

namespace ivd::math
{
struct CORE_API color
{
public:
    using dtype = std::uint8_t;

public:
    constexpr color() = default;
    constexpr color(dtype in_r, dtype in_g, dtype in_b, dtype in_a)
        : r(in_r), g(in_g), b(in_b), a(in_a)
    {
    }

    static const color white;
    static const color red;
    static const color green;
    static const color blue;

public:
    union {
        struct
        {
            dtype r, g, b, a;
        };
        std::uint32_t bits;
    };
};

} // namespace ivd::math

using color = ivd::math::color;
