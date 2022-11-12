
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

template <class Target, size_t I>
constexpr auto func_name_v =
    Target::template detail_function_reflection<I, struct detail_function_tag>::m_name;

template <class Target, size_t I>
using func_type_t =
    typename Target::template detail_function_reflection<I, struct detail_function_tag>::
        template type<Target>;

template <class Target, size_t I>
using func_trait_t = func_traits<func_type_t<Target, I>>;

template <class Target, std::size_t I>
constexpr auto func_ptr_v =
    Target::template detail_function_reflection<I, struct detail_function_tag>::
        template offset_v<Target>;

template <class Target>
constexpr size_t count_function =
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
        static constexpr std::string_view m_name = #NAME;                                \
        template <class Target>                                                          \
        using type = func_type<Target, __VA_ARGS__>;                                     \
        template <class Target>                                                          \
        static constexpr type<Target> offset_v = &Target::NAME;                          \
    };

template <class T, std::size_t Index>
struct dummy_t
{
};
class refl_func_t
{

public:
    template <class Target, std::size_t Index>
    refl_func_t(dummy_t<Target, Index>)
    {
        using func  = func_type_t<Target, Index>;
        using trait = method_traits<func>;

        using func_type = actual_func_t<typename trait::result_type,
                                        typename trait::args_type,
                                        Target,
                                        Index>;

        m_instance = std::make_unique<func_type>();
        m_argc     = trait::args_count;
        m_name     = func_name_v<Target, Index>;
    }

public:
    template <typename R, typename... Args>
    R Invoke(void* ptr, Args... args)
    {
        using interface_type = interface_t<R, std::tuple<Args...>>;
        auto iface           = static_cast<interface_type*>(m_instance.get());
        return iface->InvokeInternal(ptr, std::forward_as_tuple(args...));
    }

private:
    struct holder_t
    {
    };

    template <typename R, typename T>
    struct interface_t : public holder_t
    {
    };

    template <typename R, typename... Args>
    struct interface_t<R, std::tuple<Args...>> : public holder_t
    {
        virtual R InvokeInternal(void* obj, std::tuple<Args...>) { return {}; }
    };
    template <typename R, typename T, class Target, std::size_t Index>
    struct actual_func_t : public interface_t<R, T>
    {
        using type        = func_type_t<Target, Index>;
        using trait       = method_traits<type>;
        using result_type = typename trait::result_type;
        using arg_type    = typename trait::args_type;
        using owner_type  = typename trait::owner_type;

        template <class Tuple, size_t... Idx>
        result_type InvokeInternalImpl(void* obj,
                                       Tuple&& args,
                                       std::index_sequence<Idx...>) requires requires
        {
            std::tuple_size_v<Tuple> == std::tuple_size_v<arg_type>;
        }
        {
            return std::invoke(ptr,
                               static_cast<owner_type*>(obj),
                               std::get<Idx>(std::forward<Tuple>(args))...);
        }

        virtual result_type InvokeInternal(void* obj, T args) override
        {
            std::cout << "Done!!" << std::tuple_size_v<T>;

            // unpack and apply
            using Indices =
                std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<T>>>;
            return InvokeInternalImpl(obj, std::forward<T>(args), Indices{});
        }

    private:
        static constexpr type ptr                = func_ptr_v<Target, Index>;
        static constexpr std::string_view m_name = func_name_v<Target, Index>;
        inline static constinit const actual_func_t<R, T, Target, Index> instance{};

    public:
        static constexpr actual_func_t<R, T, Target, Index> get_instance()
        {
            return instance;
        }
    };

private:
    std::unique_ptr<holder_t> m_instance;
    std::size_t m_argc;
    std::string_view m_name;
};

}; // namespace refl
