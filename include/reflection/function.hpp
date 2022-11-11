
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

template <class Target, size_t I>
using func_trait_t = func_traits<func_type_t<Target, I>>;

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
        refl::detail::index<struct detail_##NAME##_function_tag,                         \
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

class reflected_function_t
{
public:
    template <class Target, class Reflection>
    reflected_function_t();

private:
    template <class Target, class Reflection>
    struct function_impl_t
    {
        using type        = typename Reflection::template type<Target>;
        using trait       = func_traits<type>;
        using return_type = typename trait::result_type;

    private:
        static constexpr type ptr                = Reflection::template offset_v<Target>;
        static constexpr std::string_view m_name = Reflection::m_name;
    };

private:
};
}; // namespace refl
