
#pragma once

#include "reflection_utils.hpp"
#include "reflection_concepts.hpp"
#include "reflection_types.hpp"
#include "meta/type_list.hpp"
#include "meta/array.hpp"

#include <array>
#include <type_traits>

namespace refl
{

// field reflection
template <class Target, std::size_t I>
using reflected_field = typename Target::template detail_field_reflection<I>;

template <class Target, size_t I>
constexpr auto field_name_v = reflected_field<Target, I>::name;

template <class Target, size_t I>
using field_value_t = typename reflected_field<Target, I>::value_type;

template <class Target, size_t I>
using field_pointer_t = typename reflected_field<Target, I>::template pointer_type<Target>;

template <class Target, std::size_t I>
constexpr auto field_pointer_v = reflected_field<Target, I>::template pointer_value<Target>;

template <class Target, size_t I>
static inline constexpr auto
field_type_e()
{
    using type       = std::decay_t<field_value_t<Target, I>>;
    using value_type = std::remove_pointer_t<type>;

    if constexpr (is_reflected_type<value_type>)
    {
        if constexpr (std::is_pointer_v<type>)
        {
            return efield_type::REFLECTED_PTR;
        }
        else
        {
            return efield_type::REFLECTED;
        }
    }
    else if constexpr (refl::is_object_container<value_type>)
    {
        return efield_type::REFLECTED_OBJECT_CONTAINER;
    }
    else if constexpr (std::is_fundamental_v<value_type>)
    {
        return efield_type::PRIM;
    }
    else
    {
        return efield_type::REGULAR;
    }
}

template <class Target>
    requires is_reflected_type<Target>
constexpr std::size_t field_counts =
    detail::index<struct field_counter_tag, Target::template detail_field_reflection>::value;

template <class Target>
    requires is_reflected_type<Target>
using field_counter =
    detail::index<struct field_counter_tag, Target::template detail_field_reflection>;

// function reflection

template <class Target, std::size_t I>
using reflected_func = typename Target::template detail_function_reflection<I>;

template <class Target, std::size_t I>
constexpr auto func_name_v = reflected_func<Target, I>::name;

template <class Target, std::size_t I>
using func_pointer_t = typename reflected_func<Target, I>::template type<Target>;

template <class Target, std::size_t I>
constexpr auto func_pointer_v = reflected_func<Target, I>::template pointer_v<Target>;

template <class Target>
    requires is_reflected_type<Target>
constexpr std::size_t func_counts =
    detail::index<struct function_counter_tag, Target::template detail_function_reflection>::value;

template <class Target>
    requires is_reflected_type<Target>
using function_counter =
    detail::index<struct function_counter_tag, Target::template detail_function_reflection>;
// field and property constexpr map maker

} // namespace refl
