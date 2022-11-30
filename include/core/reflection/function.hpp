
#pragma once

#include "Detail.hpp"
#include "Concepts.hpp"
#include "traits/func_traits.hpp"
#include "type_helper.hpp"

#include <cstddef>
#include <string_view>
#include <tuple>

namespace refl
{

class RFunction
{
public:
    template <class Target, std::size_t Idx>
    static constexpr auto make_info()
    {
        return std::make_pair(get_name<Target, Idx>(), RFunction(dummy_t<Target, Idx>{}));
    }

    template <class Target, std::size_t Idx>
    static constexpr auto get_name()
    {
        return func_name_v<Target, Idx>;
    }
    constexpr auto get_name() { return m_name; }

private:
    template <class Target, std::size_t Index>
    constexpr RFunction(dummy_t<Target, Index>) : m_name(func_name_v<Target, Index>)
    {
        using func              = func_type_t<Target, Index>;
        using trait             = method_traits<func>;
        using concrete_function = strip_tuple<typename trait::result_type,
                                              Target,
                                              Index,
                                              typename trait::args_type>;
        using object_type       = typename concrete_function::type;

        m_native = static_cast<handle_t const*>(object_type::get_instance());
    }
    struct handle_t
    {
        virtual ~handle_t() = default;
    };

    template <typename R, typename... Args>
    struct FunctionInterface : public handle_t
    {
        constexpr FunctionInterface() = default;
        virtual ~FunctionInterface()  = default;

        virtual R invoke_internal(void*, Args...) const = 0;
    };
    template <typename R, class Target, std::size_t Index, typename... Args>
    struct FunctionInfo;

    template <typename R, class Target, std::size_t Index, typename T>
    struct strip_tuple;

    template <typename R, class Target, std::size_t Index, typename... Ts>
    struct strip_tuple<R, Target, Index, std::tuple<Ts...>>
    {
        using type = FunctionInfo<R, Target, Index, Ts...>;
    };

public:
    template <typename R, typename... Args>
    R invoke(void* ptr, Args... args) const
    {
        using interface_type = FunctionInterface<R, Args...>;

        auto iface = static_cast<interface_type const*>(m_native);

        std::cout << "outside:" << sizeof...(Args) << '\n';

        return iface->invoke_internal(ptr, std::forward<Args>(args)...);
    }

private:
    handle_t const* m_native;
    std::string_view const m_name;
};
template <typename R, class Target, std::size_t Index, typename... Args>
struct RFunction::FunctionInfo : public RFunction::FunctionInterface<R, Args...>
{
    using type        = func_type_t<Target, Index>;
    using trait       = method_traits<type>;
    using result_type = typename trait::result_type;
    using args_type   = typename trait::args_type;
    using owner_type  = typename trait::owner_type;

    consteval FunctionInfo() = default;

    virtual R invoke_internal(void* obj, Args... args) const override
    {
        std::cout << "internal:" << sizeof...(Args) << '\n';
        return std::invoke(
            ptr, static_cast<owner_type*>(obj), std::forward<Args>(args)...);
    }
    static constexpr FunctionInfo const* get_instance() { return &instance; }

public:
    static constexpr auto argc             = trait::args_count;
    static constexpr type ptr              = func_ptr_v<Target, Index>;
    static constexpr std::string_view name = func_name_v<Target, Index>;
    static constinit const FunctionInfo instance;
};

template <typename R, class Target, std::size_t Index, typename... Args>
constinit const RFunction::FunctionInfo<R, Target, Index, Args...>
    RFunction::FunctionInfo<R, Target, Index, Args...>::instance = {};

template <HasReflectedFunction Target, std::size_t Index>
struct function_info
{
    static consteval auto get_entry()
    {
        return refl::RFunction::make_info<Target, Index>();
    }
};

}; // namespace refl

#define INFER_FUNC_TYPE(NAME)                                                            \
    template <class C, typename... Args>                                                 \
    using inferred_type =                                                                \
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
        using type = inferred_type<Target, __VA_ARGS__>;                                 \
        template <class Target>                                                          \
        static constexpr type<Target> offset_v = &Target::NAME;                          \
    };