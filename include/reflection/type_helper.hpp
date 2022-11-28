
#pragma once
#include "detail.hpp"
#include "frozen/unordered_map.h"
#include <type_traits>

namespace refl
{

// helper templates for reflected function class
template <class Target, std::size_t I>
using refl_func_info =
    typename Target::template detail_function_reflection<I, struct detail_function_tag>;

template <class Target, std::size_t I>
constexpr auto func_name_v = refl_func_info<Target, I>::name;

template <class Target, std::size_t I>
using func_type_t = typename refl_func_info<Target, I>::template type<Target>;

template <class Target, std::size_t I>
constexpr auto func_ptr_v = refl_func_info<Target, I>::template offset_v<Target>;

template <class Target>
constexpr std::size_t count_functions =
    detail::index<struct function_counter_tag,
                  Target::template detail_function_reflection>::value;

// helper templates for reflected property class
template <class Target, std::size_t I>
using refl_prop_info =
    typename Target::template detail_property_reflection<I, struct detail_member_tag>;

template <class Target, size_t I>
constexpr auto prop_name_v = refl_prop_info<Target, I>::name;

template <class Target, size_t I>
using prop_value_t = typename refl_prop_info<Target, I>::type;

template <class Target, size_t I>
using prop_ptr_t = typename refl_prop_info<Target, I>::template ptr_type<Target>;

template <class Target, std::size_t I>
constexpr auto prop_ptr_v = refl_prop_info<Target, I>::template offset_v<Target>;

template <class Target>
constexpr std::size_t count_properties =
    detail::index<struct property_counter_tag,
                  Target::template detail_property_reflection>::value;

template <template <class, std::size_t> class Info, class Target, std::size_t Index>
    requires requires { Index > 0; }
struct to_frozen_map
{
    static constexpr auto value = Info<Target, Index - 1>::get_entry();

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

} // namespace refl
