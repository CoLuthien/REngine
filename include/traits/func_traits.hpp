
#pragma once
#include <type_traits>
#include <functional>
#include <utility>

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
    using arg_count = std::integral_constant<std::size_t, sizeof...(Args)>;
    using args_type = std::tuple<typename std::decay<Args>::type...>;
};

template <class T>
struct extract_class_info;

template <class T, class U>
struct extract_class_info<T U::*>
{
    using type = U;
};

template <typename F>
class method_traits : public func_traits<F>
{
public:
    using func_ptr   = F;
    using owner_type = typename extract_class_info<F>::type;
    // using result_type = R;
    // using arg_count = std::integral_constant<std::size_t, sizeof...(Args)>;
    // using args_type = std::tuple<typename std::decay<Args>::type...>;
};



