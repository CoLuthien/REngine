
#pragma once

#define FROZEN_LETITGO_HAS_STRING_VIEW

#include <tuple>
#include <iostream>
#include <string_view>
#include "frozen/unordered_map.h"
#include "frozen/bits/elsa_std.h"

template <typename List>
struct length
{
    static constexpr size_t of = 1 + length<typename List::next>::of;
};
template <>
struct length<null_type_list>
{
    static constexpr size_t of = 0;
};

template <class List, template <class> class F>
struct visitor
{
    static consteval void visit()
    {
        F<typename List::current>::action();
        visitor<typename List::next, F>::visit();
    }
};

template <template <class> class F>
struct visitor<null_type_list, F>
{
    static consteval void visit()
    {
    }
};

template <class List, template <class> class MetaFunc, size_t Size = 0>
requires(is_type_list<List>) struct list_to_frozen_map
{
    static constexpr auto value = MetaFunc<typename List::current>::retrieve_info(); // get a container;

    static consteval auto make_map()
    {
        return list_to_frozen_map<typename List::next, MetaFunc, length<typename List::type>::of>::recurse(value);
    }

    template <typename T, typename... Args>
    static consteval auto recurse(T v, Args... args)
    {
        return list_to_frozen_map<typename List::next, MetaFunc, Size>::recurse(value, v, args...);
    }
};

template <template <class> class MetaFunc, size_t Size>
struct list_to_frozen_map<null_type_list, MetaFunc, Size>
{
    template <typename... Args>
    static consteval auto recurse(Args... args)
    {
        return frozen::make_unordered_map({args...});
    }
};

template <typename ListType, template <typename> class MetaFunc>
using make_frozen = list_to_frozen_map<ListType, MetaFunc, length<ListType>::of>;
