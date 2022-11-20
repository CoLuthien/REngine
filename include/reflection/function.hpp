
#pragma once

#include "detail.hpp"
#include "traits/func_traits.hpp"
#include "type_helper.hpp"

#include <cstddef>
#include <string_view>
#include <tuple>

namespace refl
{

class refl_func_t
{
public:
    consteval std::pair<std::string_view, refl_func_t> make_info()
    {
        return std::make_pair(get_name(), *this);
    }

public:
    template <typename R, typename... Args>
    R invoke(void* ptr, Args... args) const
    {
        using interface_type = interface_t<R, Args...>;
        // auto iface           = static_cast<interface_type*>(m_instance.get());
        auto iface = static_cast<interface_type const*>(m_ptr);

        return iface->invoke_internal(ptr, std::forward<Args>(args)...);
    }

private:
    struct handle_t
    {
    };

    template <typename R, typename... Args>
    struct interface_t : public handle_t
    {
        constexpr interface_t() = default;
        virtual ~interface_t()  = default;

        virtual R invoke_internal(void*, Args...) const = 0;
    };
    template <typename R, class Target, std::size_t Index, typename... Args>
    struct func_object_t : public interface_t<R, Args...>
    {
        using type        = func_type_t<Target, Index>;
        using trait       = method_traits<type>;
        using result_type = typename trait::result_type;
        using args_type   = typename trait::args_type;
        using owner_type  = typename trait::owner_type;

        consteval func_object_t() = default;

        virtual R invoke_internal(void* obj, Args... args) const override
        {
            return std::invoke(
                ptr, static_cast<owner_type*>(obj), std::forward<Args>(args)...);
        }
        static constexpr func_object_t const* get_instance() { return &instance; }

    public:
        static constexpr type ptr              = func_ptr_v<Target, Index>;
        static constexpr std::string_view name = func_name_v<Target, Index>;
        static constinit const func_object_t instance;
    };

public:
    template <typename R, class Target, std::size_t Index, typename T>
    struct strip_tuple;

    template <typename R, class Target, std::size_t Index, typename... Ts>
    struct strip_tuple<R, Target, Index, std::tuple<Ts...>>
    {
        using type = func_object_t<R, Target, Index, Ts...>;
    };

    template <class Target, std::size_t Index>
    constexpr refl_func_t(dummy_t<Target, Index>) : m_name(func_name_v<Target, Index>)
    {
        using func              = func_type_t<Target, Index>;
        using trait             = method_traits<func>;
        using concrete_function = strip_tuple<typename trait::result_type,
                                              Target,
                                              Index,
                                              typename trait::args_type>;
        using object_type       = typename concrete_function::type;

        m_ptr = static_cast<handle_t const*>(object_type::get_instance());
    }
    constexpr std::string_view const get_name() const { return m_name; }

private:
    handle_t const* m_ptr;
    std::string_view const m_name;
};

template <typename R, class Target, std::size_t Index, typename... Args>
constinit const refl_func_t::func_object_t<R, Target, Index, Args...>
    refl_func_t::func_object_t<R, Target, Index, Args...>::instance = {};

template <class Target, std::size_t Index>
struct function_info
{
    static consteval std::pair<std::string_view, refl::refl_func_t> get_entry()
    {
        return refl::refl_func_t(refl::dummy_t<Target, Index>()).make_info();
    }
};

}; // namespace refl

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