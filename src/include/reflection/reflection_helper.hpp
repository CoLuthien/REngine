
#pragma once

#include "reflection_utils.hpp"
#include "reflection_concepts.hpp"
#include <frozen/unordered_map.h>
#include <type_traits>

namespace refl
{

// field reflection
template <class Target, std::size_t I>
using reflected_field =
    typename Target::template detail_field_reflection<I, struct detail_member_tag>;

template <class Target, size_t I>
constexpr auto field_name_v = reflected_field<Target, I>::name;

template <class Target, size_t I>
using field_value_t = typename reflected_field<Target, I>::value_type;

template <class Target, size_t I>
using field_pointer_t =
    typename reflected_field<Target, I>::template pointer_type<Target>;

template <class Target, std::size_t I>
constexpr auto field_pointer_v = reflected_field<Target, I>::template pointer_value<Target>;

template <class Target>
constexpr std::size_t field_counts =
    detail::index<struct field_counter_tag,
                  Target::template detail_field_reflection>::value;

// function reflection

template <class Target, std::size_t I>
using reflected_func =
    typename Target::template detail_function_reflection<I, struct detail_function_tag>;

template <class Target, std::size_t I>
constexpr auto func_name_v = reflected_func<Target, I>::name;

template <class Target, std::size_t I>
using func_pointer_t = typename reflected_func<Target, I>::template type<Target>;

template <class Target, std::size_t I>
constexpr auto func_pointer_v = reflected_func<Target, I>::template pointer_v<Target>;

template <class Target>
constexpr std::size_t func_counts =
    detail::index<struct function_counter_tag,
                  Target::template detail_function_reflection>::value;

// field and property constexpr map maker
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
