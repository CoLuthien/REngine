
#pragma once

#include <type_traits>
#include <utility>

namespace meta
{

template <typename E>
constexpr auto
to_underlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}

} // namespace meta
