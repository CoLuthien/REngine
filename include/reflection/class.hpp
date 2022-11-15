
#pragma once

#include "type_helper.hpp"
#include <cstddef>
#include <string_view>
#include "frozen/unordered_map.h"
#include "frozen/bits/elsa_std.h"

namespace refl
{

template <class Target, std::size_t Index>
struct property_info
{
    static consteval std::pair<std::string_view, refl::refl_prop_t> get()
    {
        return std::make_pair(
            refl::refl_prop_t(refl::dummy_t<Target, Index>()).get_name(),
            refl::refl_prop_t(refl::dummy_t<Target, Index>()));
    }
};

template <class Target, std::size_t Index>
struct function_info
{
    static consteval std::pair<std::string_view, refl::refl_func_t> get()
    {
        return std::make_pair(
            refl::refl_func_t(refl::dummy_t<Target, Index>()).get_name(),
            refl::refl_func_t(refl::dummy_t<Target, Index>()));
    }
};

template <template <class, std::size_t> class Info, class Target, std::size_t Index>
struct to_frozen_map
{
    static constexpr auto value = Info<Target, Index - 1>::get(); // get a container;

    static consteval auto make_map()
    {
        return to_frozen_map<Info, Target, Index - 1>::recurse(value);
    }

    template <typename T, typename... Args>
    static consteval auto recurse(T v, Args... args)
    {
        return to_frozen_map<Info, Target, Index - 1>::recurse(value, v, args...);
    }
};

template <template <class, std::size_t> class Info, class Target>
struct to_frozen_map<Info, Target, 0>
{
    template <typename... Args>
    static consteval auto recurse(Args... args)
    {
        return frozen::make_unordered_map({args...});
    }
};

class refl_class_t
{
public:
private:
};

} // namespace refl
