
#pragma once

#include "constants.hpp"
#include <cmath>
#include <numbers>

namespace ivd
{
namespace math
{

namespace ops
{

#ifdef USE_STD_MATH

using std::atan;
using std::cos;
using std::sin;

using std::sqrt;

template <typename T>
static consteval T
const_pi()
{
    return std::numbers::pi_v<T>;
}

#endif

} // namespace ops

template <typename T>
static constexpr T epsilon = 1e-5;

template <typename T>
static constexpr T pi = ops::const_pi<T>();

template <typename T>
static constexpr T degree_to_rad = pi<T> / 180.;

} // namespace math

} // namespace ivd