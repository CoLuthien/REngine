
#pragma once

#include "core/definitions.hpp"
#include "math/point.hpp"

namespace ivd
{

namespace math
{

template <typename T>
struct vector2 : public point2<T>
{
    // todo ...
};

template <typename T>
struct vector3 : public point3<T>
{
    // todo ...
};

} // namespace math

using vector2_f = math::vector2<float>;
using vector3_f = math::vector3<float>;

} // namespace ivd