
#pragma once

#include "detail.hpp"
#include "traits/func_traits.hpp"
#include "type_helper.hpp"

#include <cstddef>
#include <string_view>
#include <memory>
#include <tuple>

namespace refl
{

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

#define INFER_FUNC_TYPE(NAME)                                                            \
    template <class C, typename... Args>                                                 \
    using func_type =                                                                    \
        decltype(std::declval<C>().NAME(std::declval<Args>()...)) (C::*)(Args...);

#define REFLECT_FUNCTION(NAME, ...)                                                      \
    template <std::size_t, class>                                                        \
    struct detail_function_reflection;                                                   \
    static constexpr size_t detail_##NAME##_function_index =                             \
        refl::detail::index<struct detail_##NAME##_function_tag,                         \
                            detail_function_reflection>::value;                          \
    template <class T>                                                                   \
    struct detail_function_reflection<detail_##NAME##_function_index, T>                 \
    {                                                                                    \
        INFER_FUNC_TYPE(NAME);                                                           \
        static constexpr std::string_view name = #NAME;                                  \
        template <class Target>                                                          \
        using type = func_type<Target, __VA_ARGS__>;                                     \
        template <class Target>                                                          \
        static constexpr type<Target> offset_v = &Target::NAME;                          \
    };

class refl_func_t
{

public:
    template <class Target, std::size_t Index>
    constexpr refl_func_t(dummy_t<Target, Index>) : m_name(func_name_v<Target, Index>)
    {
        using func  = func_type_t<Target, Index>;
        using trait = method_traits<func>;

        using interface_type =
            interface_t<typename trait::result_type, typename trait::args_type>;
        using object_type = func_object_t<typename trait::result_type,
                                          typename trait::args_type,
                                          Target,
                                          Index>;

        m_ptr = static_cast<handle_t const*>(object_type::get_instance());
    }
    consteval std::string_view const get_name() const { return m_name; }

public:
    template <typename R, typename... Args>
    R invoke(void* ptr, Args... args) const
    {
        using interface_type = interface_t<R, std::tuple<Args...>>;
        // auto iface           = static_cast<interface_type*>(m_instance.get());
        auto iface = static_cast<interface_type const*>(m_ptr);

        return iface->invoke_internal(ptr, std::forward_as_tuple(args...));
    }

private:
    struct handle_t
    {
    };

    template <typename R, typename T>
    struct interface_t;

    template <typename R, typename... Args>
    struct interface_t<R, std::tuple<Args...>> : public handle_t
    {
        constexpr interface_t() = default;
        virtual ~interface_t()  = default;

        virtual R invoke_internal(void* obj, std::tuple<Args...>) const = 0;
    };
    template <typename R, typename T, class Target, std::size_t Index>
    struct func_object_t : public interface_t<R, T>
    {
        using type        = func_type_t<Target, Index>;
        using trait       = method_traits<type>;
        using result_type = typename trait::result_type;
        using args_type   = typename trait::args_type;
        using owner_type  = typename trait::owner_type;

        consteval func_object_t() = default;

        template <class Tuple, size_t... Idx>
        R invoke_internal_impl(void* obj, Tuple&& args, std::index_sequence<Idx...>) const
        {
            return std::invoke(ptr,
                               static_cast<owner_type*>(obj),
                               std::get<Idx>(std::forward<Tuple>(args))...);
        }

        virtual R invoke_internal(void* obj, T args) const override
        {
            using Indices =
                std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<T>>>;
            // unpack and apply
            return invoke_internal_impl(obj, std::forward<T>(args), Indices{});
        }
        static constexpr func_object_t const* get_instance() { return &instance; }

    public:
        static constexpr type ptr              = func_ptr_v<Target, Index>;
        static constexpr std::string_view name = func_name_v<Target, Index>;
        static constinit const func_object_t instance;
    };

private:
    handle_t const* m_ptr;
    std::string_view const m_name;
};

template <typename R, typename T, class Target, std::size_t Index>
constinit const refl_func_t::func_object_t<R, T, Target, Index>
    refl_func_t::func_object_t<R, T, Target, Index>::instance = {};

}; // namespace refl
