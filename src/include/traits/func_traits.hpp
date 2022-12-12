
#pragma once

#include <type_traits>
#include <tuple>

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
