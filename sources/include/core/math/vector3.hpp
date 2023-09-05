
#pragma once

#include "core/definitions.hpp"
#include "point.hpp"

namespace ivd
{

namespace math
{

template <typename T>
struct vector3 : public point3<T>
{
public:
    constexpr vector3() = default;
    constexpr vector3(T value) : point3<T>(value) {}
    constexpr vector3(T in_x, T in_y, T in_z) : point3<T>(in_x, in_y, in_z) {}

public:
    using point3<T>::x;
    using point3<T>::y;
    using point3<T>::z;
};

} // namespace math

} // namespace ivd