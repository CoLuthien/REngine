
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
public:
    T x, y;
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
