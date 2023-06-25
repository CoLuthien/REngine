
#pragma once

#include "core/definitions.hpp"

namespace ivd
{
namespace math
{

template <typename T>
struct point2
{
public:
    point2() = default;
    point2(T in_x, T in_y) : x(in_x), y(in_y) {}
    point2(T in_value) : x(in_value), y(in_value) {}

public:
    point2<T> operator+(T value) { return point2<T>{x + value, y + value}; }

public:
    T x = {}, y = {};
};

template <typename T>
struct point3
{
public:
public:
    T x, y, z;
};
} // namespace math

using point2_f = math::point2<float>;
using point3_f = math::point3<float>;

} // namespace ivd
