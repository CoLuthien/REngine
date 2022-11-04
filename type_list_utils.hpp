
#pragma once

#include <tuple>
#include <string_view>
#include <iostream>
#include "frozen/bits/elsa_std.h"
#include "frozen/unordered_map.h"

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

template <class List, template <class> class F>
struct flatten_to_type
{
    static constexpr auto value = F<typename List::current>::action(); // get a container;

    static consteval auto get()
    {
        return next();
    }
    static consteval auto next()
    {
        return flatten_to_type<typename List::next, F>::next(value);
    }

    template <typename T, typename... Args>
    static consteval auto next(T v, Args... args)
    {
        return flatten_to_type<typename List::next, F>::next(value, v, args...);
    }
};

template <template <class> class F>
struct flatten_to_type<void, F>
{
    template <typename... Args>
    static consteval auto next(Args... args)
    {
        // std::cout << "print out types : ";
        //((std::cout << (args) << " "), ...);
        auto const p = std::initializer_list<std::pair<std::string_view, int>>{{args}...};
        return frozen::unordered_map<std::string_view, int, 2>(p);
    }
};
