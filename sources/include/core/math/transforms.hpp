
#pragma once

#include "math/point.hpp"
#include "math/vector.hpp"
#include "math/extent.hpp"

namespace ivd
{

template <typename T>
math::vector2<T>
scale(T const& amount, math::vector2<T> const& orig)
{
    return amount * orig;
}

template <typename T>
math::point2<T>
translate(math::point2<T> const& original, math::extent2<T> const& amount)
{
    return math::point2<T>{original.x + amount.x, original.y + amount.y};
}

template <typename T>
math::point2<T>
translate(math::point2<T> const& original, T amount)
{
    return original + amount;
}

template <typename T>
constexpr math::extent2<T>
as_extent(math::point2<T> const& value)
{
    return {value.x, value.y};
}
} // namespace ivd