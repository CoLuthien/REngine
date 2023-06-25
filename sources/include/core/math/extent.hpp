
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
    T x, y;
};

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