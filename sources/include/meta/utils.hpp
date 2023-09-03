
#pragma once

#include <type_traits>
#include <utility>
#include <concepts>
#include <vector>

namespace meta
{

template <typename T>
using remove_all_qualifiers_t = std::decay_t<std::remove_pointer_t<T>>;

template <typename E>
static constexpr auto
to_underlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}
template <class, template <class...> class>
inline constexpr bool is_specialization = false;

template <template <class...> class T, class... Args>
inline constexpr bool is_specialization<T<Args...>, T> = true;

} // namespace meta
