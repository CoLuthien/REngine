
#pragma once

#include "reflection_utils.hpp"
#include "reflection_concepts.hpp"
#include "meta/type_list.hpp"
#include "meta/array.hpp"
#include "reflection_helper.hpp"

#include <array>
#include <frozen/unordered_map.h>
#include <type_traits>

namespace refl
{

template <template <class, std::size_t> class Info, class Target, std::size_t Index>
    requires requires { Index > 0; }
struct to_array
{
    static constexpr auto value = Info<Target, Index - 1>::get_entry();

    static consteval auto entry_point() { return recurse(); }

    template <typename... Args>
    static consteval auto recurse(Args... args)
    {
        return to_array<Info, Target, Index - 1>::recurse(value, args...);
    }
};

template <template <class, std::size_t> class Info, class Target>
struct to_array<Info, Target, 0>
{
    static consteval auto entry_point()
    {
        using type =
            decltype(Info<Target, std::numeric_limits<std::size_t>::max()>::get_entry());
        return std::array<type, 1>{};
    }
    template <typename... Args>
    static consteval auto recurse(Args... args)
    {
        return std::array{args...};
    }
};

template <typename List, template <class, std::size_t> class R, template <class> class C>
struct reflect_all_t
{
    static constexpr auto info =
        to_array<R, typename List::current, C<typename List::current>::value>::
            entry_point();

    static inline consteval auto entry() { return recurse(); }

    static inline consteval auto recurse()
    {
        return meta::array::cat(info,
                                reflect_all_t<typename List::next, R, C>::recurse());
    }
};

template <template <class, std::size_t> class R, template <class> class C>
struct reflect_all_t<meta::null_list, R, C>
{
    static inline consteval auto entry() { return recurse(); }
    static inline consteval auto recurse() { return nullptr; }
};
} // namespace refl