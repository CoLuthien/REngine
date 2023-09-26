
#pragma once

#include <type_traits>
#include <utility>
#include <concepts>
#include <vector>
#include <string_view>
#include <ranges>

namespace meta
{
namespace detail
{
static constexpr std::uint64_t
fnv1a_64(char const* s, std::size_t count)
{
    return ((count ? fnv1a_64(s, count - 1) : 14695981039346656037u) ^ s[count]) * 1099511628211u;
}

static constexpr auto
hash(std::string_view view)
{
    return fnv1a_64(view.data(), view.size());
}

template <typename T>
struct type_name
{
    static constexpr std::string_view mangled_name()
    {
#if defined(__clang__) || defined(__GNUC__)
        return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
        return __FUNCSIG__;
#else
#error "Unsupported compiler"
#endif
    }

    using type = T;

    static constexpr std::string_view value = mangled_name();
};

} // namespace detail

template <class T>
static constexpr auto type_name_v = detail::type_name<T>::value;

template <class T>
static constexpr auto typehash = detail::hash(type_name_v<T>);

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

template <typename T>
concept is_iterable_type = std::ranges::range<T>;

} // namespace meta
