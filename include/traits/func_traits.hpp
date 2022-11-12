
#pragma once
#include <type_traits>
#include <functional>
#include <utility>
#include <iostream>

template <class T>
struct extract_class_info;

template <class T, class U>
struct extract_class_info<T U::*>
{
    using type = U;
};

template <typename T>
struct func_traits : func_traits<decltype(&T::operator())>
{
};

template <typename C, typename R, typename... Args>
struct func_traits<R (C::*)(Args...)> : func_traits<R (*)(Args...)>
{
};

template <typename C, typename R, typename... Args>
struct func_traits<R (C::*)(Args...) const> : func_traits<R (*)(Args...)>
{
};

template <typename R, typename... Args>
struct func_traits<R (*)(Args...)>
{
    using result_type = R;
    static constexpr auto args_count =
        std::integral_constant<std::size_t, sizeof...(Args)>::value;
    using args_type = std::tuple<typename std::decay<Args>::type...>;
};

template <class F>
struct method_traits : public func_traits<F>
{
    using type       = F;
    using owner_type = std::decay_t<typename extract_class_info<F>::type>;
};

template <class T>
struct strip_base;

template <class... Ts>
struct strip_base<std::tuple<Ts...>>
{
};

template <class F, class Tuple>
struct extract_tuple_and_apply;

template <class F, class... Ts>
struct extract_tuple_and_apply<F, std::tuple<Ts...>>
{
    using R = typename method_traits<F>::result_type;
    using C = typename method_traits<F>::owner_type;
    static R apply(F ptr, void* object, Ts... args)
    {
        return std::invoke(ptr, *static_cast<C*>(object), args...);
    }
};

template <typename F>
using strip_types = extract_tuple_and_apply<F, typename method_traits<F>::args_type>;
