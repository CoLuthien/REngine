
#pragma once

#include <type_traits>
#include <utility>
#include <array>

namespace meta
{

namespace array
{
template <typename T, typename U, std::size_t... N, std::size_t... M>
static inline consteval auto cat_impl(T x,
                                      U y,
                                      std::index_sequence<N...>,
                                      std::index_sequence<M...>);

template <typename T>
static inline consteval auto
cat(T x, std::nullptr_t)
{
    return x;
}

template <typename T, typename U>
static inline consteval auto
cat(T x, U y)
{
    return cat_impl(
        x, y, std::make_index_sequence<x.size()>{}, std::make_index_sequence<y.size()>{});
}

template <typename T, typename U, std::size_t... N, std::size_t... M>
static inline consteval auto
cat_impl(T x, U y, std::index_sequence<N...>, std::index_sequence<M...>)
{
    return std::array{x[N]..., y[M]...};
}

} // namespace array

} // namespace meta
