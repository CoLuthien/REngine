
#pragma once

#include "reflection_utils.hpp"
#include "reflection_concepts.hpp"
#include "meta/type_list.hpp"
#include "meta/array.hpp"
#include "reflection_helper.hpp"

#include <array>
#include <vector>
#include <frozen/unordered_map.h>
#include <type_traits>

namespace refl
{

template <template <class, std::size_t> class Info, class Target, std::size_t Index>
    requires requires { Index > 0; }
struct as_initializer_list
{
    static constexpr auto value = Info<Target, Index - 1>::get_entry();

    static consteval auto entry_point() { return recurse(); }

    template <typename... Args>
    static consteval auto recurse(Args... args)
    {
        return as_initializer_list<Info, Target, Index - 1>::recurse(value, args...);
    }
};

template <template <class, std::size_t> class Info, class Target>
struct as_initializer_list<Info, Target, 0>
{
    static consteval auto entry_point()
    {
        using type =
            decltype(Info<Target, std::numeric_limits<std::size_t>::max()>::get_entry());
        return std::initializer_list<type>{};
    }
    template <typename... Args>
    static consteval auto recurse(Args... args)
    {
        return std::initializer_list{args...};
    }
};

} // namespace refl