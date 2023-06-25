
#pragma once

#include "core/definitions.hpp"

#include <cstdint>

namespace ivd::math
{
template <typename T>
struct color
{

public:
    T r, g, b, a;
};

} // namespace ivd::math

namespace ivd
{
using linear_color = math::color<float>;
using color        = math::color<std::uint8_t>;
} // namespace ivd