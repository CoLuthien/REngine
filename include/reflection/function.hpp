
#pragma once

#include "detail.hpp"
#include "traits/func_traits.hpp"

#include <cstddef>
#include <string_view>

namespace refl
{

template <class Target, size_t I>
constexpr auto func_name_v =
    Target::template detail_function_reflection<I, struct detail_function_tag>::name;

template <class Target, size_t I>
using func_type_t =
    typename Target::template detail_function_reflection<I, struct detail_function_tag>::
        template type<Target>;

template <class Target, std::size_t I>
constexpr auto ptr_to_function =
    Target::template detail_function_reflection<I, struct detail_function_tag>::
        template offset_v<Target>;

template <class Target>
constexpr size_t count_function =
    detail::index<struct counter_tag, Target::template detail_function_reflection>::value;

#define INFER_FUNC_TYPE(NAME)                                                            \
    template <class C, typename... Args>                                                 \
    using func_type =                                                                    \
        decltype(std::declval<C>().NAME(std::declval<Args>()...)) (C::*)(Args...);

#define REFLECT_FUNCTION(NAME, ...)                                                      \
    template <size_t, class>                                                             \
    struct detail_function_reflection;                                                   \
    static constexpr std::size_t detail_##NAME##_function_index =                        \
        refl::detail::index<struct detail_##NAME##_tag,                                  \
                            detail_function_reflection>::value;                          \
    template <class Tag>                                                                 \
    struct detail_function_reflection<detail_##NAME##_function_index, Tag>               \
    {                                                                                    \
        INFER_FUNC_TYPE(NAME);                                                           \
        static constexpr std::string_view m_name = #NAME;                                \
        template <class Target>                                                          \
        using type = func_type<Target, __VA_ARGS__>;                                     \
        template <class Target>                                                          \
        static constexpr type<Target> offset_v = &Target::NAME;                          \
    };
}; // namespace refl

/*
    using T1 = detail_member_reflection<0, TargetClass>;
    //...
*/
