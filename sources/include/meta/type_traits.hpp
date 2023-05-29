
#pragma once

#include <type_traits>

namespace meta
{

template <typename T>
static constexpr auto
to_underlying(T value)
{
    return static_cast<std::underlying_type_t<T>>(value);
}


} // namespace meta