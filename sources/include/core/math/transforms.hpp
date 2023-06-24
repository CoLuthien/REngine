
#pragma once

#include "core/definitions.hpp"
#include "math/point.hpp"
#include "math/vector.hpp"
#include "math/extent.hpp"

namespace ivd
{

template <typename T>
math::vector2<T>
scale(T amount, math::vector2<T> orig)
{
    return amount * orig;
}

template <typename T>
math::point2<T>
translate(math::point2<T> transform, math::point2<T> orig)
{
    return orig + transform;
}

} // namespace ivd