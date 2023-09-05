
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
    constexpr point2() = default;
    constexpr point2(T in_x, T in_y) : x(in_x), y(in_y) {}

    template <typename U>
    constexpr point2(U in_x, U in_y);

public:
    T x{}, y{};
};

template <typename T>
template <typename U>
constexpr point2<T>::point2(U in_x, U in_y)
{
    x = (T)in_x;
    y = (T)in_y;
}

} // namespace math

} // namespace ivd
