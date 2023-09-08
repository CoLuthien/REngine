
#pragma once

#include "core/definitions.hpp"
#include "point.hpp"
#include "basics.hpp"

#include "core_object.hpp"

namespace ivd
{

namespace math
{

template <meta::arithmetic_type T>
struct vector3
{
    GENERATE_STRUCT();

public:
    constexpr vector3() = default;
    constexpr vector3(T value) : x(value), y(value), z(value) {}
    constexpr vector3(T in_x, T in_y, T in_z) : x(in_x), y(in_y), z(in_z) {}

public:
    T          squared_norm() const { return x * x + y * y + z * z; }
    T          norm() const { return ops::sqrt(squared_norm()); }
    bool       normalize(T const eps = epsilon<T>) const;
    vector3<T> normalized(T const eps = epsilon<T>) const;

public:
    REFLECT_FIELD(T, x);
    REFLECT_FIELD(T, y);
    REFLECT_FIELD(T, z);
};

template <meta::arithmetic_type T>
bool
vector3<T>::normalize(T const eps) const
{
    T length = norm();
    if (length > eps)
    {
        *this = (*this) / length;
        return true;
    }
    return false;
}

template <meta::arithmetic_type T>
vector3<T>
vector3<T>::normalized(T const eps) const
{
    T length = norm();
    if (length > eps)
    {
        return (*this) / length;
    }

    return {};
}

template <meta::arithmetic_type T, meta::arithmetic_type U>
inline vector3<T>
operator/(vector3<T> const& v, U scale)
{
    T x = v.x / static_cast<T>(scale);
    T y = v.y / static_cast<T>(scale);
    T z = v.z / static_cast<T>(scale);
    return vector3<T>(x, y, z);
}

template <meta::arithmetic_type T, meta::arithmetic_type U>
inline vector3<T>
operator*(vector3<T> const& v, U scale)
{
    T x = v.x * static_cast<T>(scale);
    T y = v.y * static_cast<T>(scale);
    T z = v.z * static_cast<T>(scale);
    return vector3<T>(x, y, z);
}

template <meta::arithmetic_type T, meta::arithmetic_type U>
inline vector3<T>
operator*(U scale, vector3<T> const& v)
{
    return v * scale;
}

template <meta::arithmetic_type T>
inline vector3<T>
operator*(vector3<T> const& u, vector3<T> const& v)
{
    T x = u.x * v.x;
    T y = u.y * v.y;
    T z = u.z * v.z;
    return vector3<T>(x, y, z);
}

} // namespace math

} // namespace ivd