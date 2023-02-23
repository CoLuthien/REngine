
#pragma once

#include "reflection_utils.hpp"
#include "reflection_concepts.hpp"
#include "meta/type_list.hpp"
#include "meta/array.hpp"

#include <array>
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
constexpr auto field_pointer_v =
    reflected_field<Target, I>::template pointer_value<Target>;

template <class Target>
    requires is_reflected_type<Target>
constexpr std::size_t field_counts =
    detail::index<struct field_counter_tag,
                  Target::template detail_field_reflection>::value;

template <class Target>
    requires is_reflected_type<Target>
using field_counter =
    detail::index<struct field_counter_tag, Target::template detail_field_reflection>;

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
    requires is_reflected_type<Target>
constexpr std::size_t func_counts =
    detail::index<struct function_counter_tag,
                  Target::template detail_function_reflection>::value;

template <class Target>
    requires is_reflected_type<Target>
using function_counter = detail::index<struct function_counter_tag,
                                       Target::template detail_function_reflection>;
// field and property constexpr map maker
template <template <class, std::size_t> class Info, class Target, std::size_t Index>
    requires requires { Index > 0; }
struct to_array
{
    static constexpr auto value = Info<Target, Index - 1>::get_entry();

    static consteval auto make_map()
    {
        return to_array<Info, Target, Index - 1>::recurse(value);
    }

    template <typename... Args>
    static consteval auto recurse(Args... args)
    {
        return to_array<Info, Target, Index - 1>::recurse(value, args...);
    }
};

template <template <class, std::size_t> class Info, class Target>
struct to_array<Info, Target, 0>
{
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
        to_array<R, typename List::current, C<typename List::current>::value>::make_map();

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
    static inline consteval auto recurse() { return nullptr; }
};

} // namespace refl
