
#pragma once
#include <type_traits>
#include <functional>
#include <utility>

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
    static constexpr auto arg_count =
        std::integral_constant<std::size_t, sizeof...(Args)>::value;
    using args_type = std::tuple<typename std::decay<Args>::type...>;
};

template <class F>
struct method_traits : public func_traits<F>
{
    using type       = F;
    using owner_type = typename extract_class_info<F>::type;
};

template <class T>
struct strip
{
    static void func() { std::cout << "Hello"; }
};

template <class... Ts>
struct strip<std::tuple<Ts...>>
{
    static void func() { std::cout << "World"; }
};

template <class F, class T>
struct strip_and_apply
{
    static void func() { std::cout << "World"; }
};

template <class F, class... Ts>
struct strip_and_apply<F, std::tuple<Ts...>>
{
    using R = typename method_traits<F>::result_type;
    using C = typename method_traits<F>::owner_type;
    static R func(void* ptr, C& c, Ts... args) { return std::invoke(ptr, c, args...); }
};
