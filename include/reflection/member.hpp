
#pragma once

#include <cstddef>
#include <string_view>
#include "detail.hpp"

namespace refl
{

template <class Target, size_t I>
constexpr auto member_name_v =
    Target::template detail_member_reflection<I, struct detail_member_tag>::name;

template <class Target, size_t I>
using member_type_t =
    typename Target::template detail_member_reflection<I, struct detail_member_tag>::type;

template <class Target, std::size_t I>
constexpr auto ptr_to_member_var =
    Target::template detail_member_reflection<I, struct detail_member_tag>::
        template offset_v<Target>;

template <class Target>
constexpr size_t count_variable =
    detail::index<struct counter_tag, Target::template detail_member_reflection>::value;

#define REFLECT_MEMBER(NAME, ...)                                                        \
    __VA_ARGS__ NAME;                                                                    \
    template <size_t, class>                                                             \
    struct detail_member_reflection;                                                     \
    static constexpr size_t detail_##NAME##_member_index =                               \
        refl::detail::index<struct detail_##NAME##_tag,                                  \
                            detail_member_reflection>::value;                            \
    template <class T>                                                                   \
    struct detail_member_reflection<detail_##NAME##_member_index, T>                     \
    {                                                                                    \
        using type                             = __VA_ARGS__;                            \
        static constexpr std::string_view name = #NAME;                                  \
        template <class U>                                                               \
        static constexpr type U::*offset_v = &U::NAME;                                   \
    };

/*
    using T1 = detail_member_reflection<0, TargetClass>;
    //...
*/

} // namespace refl
