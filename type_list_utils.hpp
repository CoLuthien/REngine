
#pragma once

#include <tuple>
#include <string_view>

template <typename List>
struct length
{
    static constexpr size_t of = 1 + length<typename List::next>::of;
};
template <>
struct length<void>
{
    static constexpr size_t of = 0;
};

template <class List, template <class> class F>
struct visitor
{
    static consteval void visit()
    {
        F<typename List::current>::action();      // get a return value;
        visitor<typename List::next, F>::visit(); // get a container;
        // need flatten
    }
};

template <template <class> class F>
struct visitor<void, F>
{
    static consteval void visit()
    {
    }
};

template <class List, template <class> class F, class... Ts>
struct flatten_to_type
{
    static constexpr auto value = F<typename List::current>::action(); // get a return value;
    static auto get()
    {
        return flatten_to_type<typename List::next, F, Ts...>::next(value); // get a container;
    }
    static auto next(Ts... v, Ts... vs)
    {
        return flatten_to_type<typename List::next, F, Ts...>::next(v..., vs...); // get a container;
    }
};

template <template <class> class F, class... Ts>
struct flatten_to_type<void, F, Ts...>
{
    static auto next(Ts... v, Ts... vs)
    {
        return std::initializer_list<std::string_view>{v..., vs...};
    }
};
