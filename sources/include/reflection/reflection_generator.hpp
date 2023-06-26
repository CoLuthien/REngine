
#pragma once

#include "reflection_utils.hpp"
#include "reflection_concepts.hpp"
#include "meta/type_list.hpp"
#include "meta/array.hpp"
#include "reflection_helper.hpp"

#include <type_traits>
#include <string_view>
#include <numeric>
#include <array>
#include <vector>

namespace refl
{

template <template <class, std::size_t> class Info, class Target, std::size_t Index>
    requires requires { Index > 0; }
struct as_initializer_list
{
    static constexpr auto value = Info<Target, Index - 1>::get_entry();

    static consteval auto entry_point() { return recurse(); }

    template <typename... Args>
    static consteval auto recurse(Args const&... args)
    {
        return as_initializer_list<Info, Target, Index - 1>::recurse(value, args...);
    }
};

template <template <class, std::size_t> class Info, class Target>
struct as_initializer_list<Info, Target, 0>
{

    using type = decltype(Info<Target, std::numeric_limits<std::size_t>::max()>::get_entry());
    static consteval auto entry_point() { return std::array<type, 0>{}; }
    template <typename... Args>
    static consteval auto recurse(Args const&... args)
    {
        return std::array{args...};
    }
};

} // namespace refl