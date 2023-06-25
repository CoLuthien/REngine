
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
public:
    using point2<T>::x;
    using point2<T>::y;

public:
    inline constexpr vector2<T> operator*(T scale) { return vector2<T>{scale * x, scale * y}; }
    inline constexpr vector2<T> operator/(T scale) { return vector2<T>{x / scale, y / scale}; }
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