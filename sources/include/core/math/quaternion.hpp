
#pragma once

#include "core/definitions.hpp"
#include "constants.hpp"

#include <concepts>
#include <cmath>

namespace ivd
{

namespace math
{

template <std::floating_point T>
struct quaternion
{
public:
    T i, j, k, w;

public:
    constexpr quaternion() = default;
    constexpr quaternion(T in_w, T in_i, T in_j, T in_k);
    constexpr quaternion(quaternion<T> const& other);

    template <std::floating_point U>
    explicit constexpr quaternion(quaternion<U> const& other);

public:
    T squred_norm() const { return i * i + j * j + k * k + w * w; }
    T norm() const { return std::sqrt(squred_norm()); }

    T          normalize(T const eps = epsilon<T>);
    quaternion normalized(T const eps = epsilon<T>) const;

    quaternion inverse() const;
};

template <std::floating_point T>
constexpr quaternion<T>::quaternion(T in_w, T in_i, T in_j, T in_k)
    : i(in_i), j(in_j), k(in_k), w(in_w)
{
}

template <std::floating_point T>
constexpr quaternion<T>::quaternion(quaternion<T> const& other)
    : i(other.i), j(other.j), k(other.k), w(other.w)
{
}

template <std::floating_point T>
template <std::floating_point U>
constexpr quaternion<T>::quaternion(quaternion<U> const& other)
{
    i = (T)other.i;
    j = (T)other.j;
    k = (T)other.k;
    w = (T)other.w;
}

template <std::floating_point T>
quaternion<T>
quaternion<T>::normalized(T const eps) const
{
    T length = norm();
    if (length > eps)
    {
        T inverted = ((T)1.) / length;
        return quaternion<T>{w * inverted, i * inverted, j * inverted, k * inverted};
    }
    return {};
}

template <std::floating_point T>
T
quaternion<T>::normalize(T const eps)
{
    T length = norm();
    if (length > eps)
    {
        T inverted = ((T)1.) / length;

        i *= inverted;
        j *= inverted;
        k *= inverted;
        w *= inverted;

        return inverted;
    }
    return {};
}

template <std::floating_point T>
quaternion<T>
quaternion<T>::inverse() const
{
    T val = i * i + j * j + k * k + w * w;

    return quaternion<T>(w / val, -(i / val), -(j / val), -(k / val));
}

template <typename T>
quaternion<T> constexpr
operator*(quaternion<T> const& a, quaternion<T> const& b)
{
    T w = a.w * b.w - (a.i * b.i) - (a.j * b.j) - (a.k * b.k);
    T i = a.w * b.i + (a.i * b.w) + (a.j * b.k) - (a.k * b.j);
    T j = a.w * b.j - (a.i * b.k) + (a.j * b.w) + (a.k * b.i);
    T k = a.w * b.k + (a.i * b.j) - (a.j * b.i) + (a.k * b.w);

    return quaternion<T>(w, i, j, k);
}

template <std::floating_point T>
quaternion<T> constexpr
operator+(quaternion<T> const& a, quaternion<T> const& b)
{
    T w = a.w + b.w;
    T i = a.i + b.i;
    T j = a.j + b.j;
    T k = a.k + b.k;

    return quaternion<T>(w, i, j, k);
}

} // namespace math

using quaternion_d = math::quaternion<double>;

} // namespace ivd