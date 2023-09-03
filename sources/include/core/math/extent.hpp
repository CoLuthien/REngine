
#pragma once

#include "core/definitions.hpp"

namespace ivd
{

namespace math
{

template <typename T>
struct extent2
{
public:
    extent2() = default;
    extent2(T in_x, T in_y) : x(in_x), y(in_y) {}

public:
    constexpr extent2<T> operator*(T scale);

public:
    T x, y;
};

template <typename T>
constexpr extent2<T>
extent2<T>::operator*(T scale)
{
    return {x * scale, y * scale};
}

template <typename T>
constexpr extent2<T>
operator-(extent2<T> const& value)
{
    return {-value.x, -value.y};
}

template <typename T>
struct extent3
{
public:
    T x, y, z;
};

template <typename T>
struct extent4
{
public:
    T x, y, z, w;
};

} // namespace math

using extent2_f = math::extent2<float>;
using extent3_f = math::extent3<float>;
using extent4_f = math::extent4<float>;

} // namespace ivd