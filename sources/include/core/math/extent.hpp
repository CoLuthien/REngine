
#pragma once

#include "core_object.hpp"

namespace ivd
{

namespace math
{

template <typename T>
struct extent2
{
public:
    GENERATE_STRUCT()
public:
    extent2() = default;
    extent2(T in_x, T in_y) : x(in_x), y(in_y) {}

public:
    constexpr extent2<T> operator*(T scale);

public:
    REFLECT_FIELD(T, x);
    REFLECT_FIELD(T, y);
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
    GENERATE_STRUCT()

public:
    REFLECT_FIELD(T, x, {});
    REFLECT_FIELD(T, y, {});
    REFLECT_FIELD(T, z, {});
};

template <typename T>
struct extent4
{
public:
    GENERATE_STRUCT()
public:
    REFLECT_FIELD(T, x, {});
    REFLECT_FIELD(T, y, {});
    REFLECT_FIELD(T, z, {});
    REFLECT_FIELD(T, w, {});
};

} // namespace math

using extent2_f = math::extent2<float>;
using extent3_f = math::extent3<float>;
using extent4_f = math::extent4<float>;

using extent2i = math::extent2<std::int32_t>;
using extent3i = math::extent3<std::int32_t>;
using extent4i = math::extent4<std::int32_t>;

using extent2u = math::extent2<std::uint32_t>;
using extent3u = math::extent3<std::uint32_t>;
using extent4u = math::extent4<std::uint32_t>;

} // namespace ivd