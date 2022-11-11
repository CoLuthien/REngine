
#pragma once

#include "type_list.hpp"

#include "frozen/bits/elsa_std.h"
#include "frozen/unordered_map.h"

#include <tuple>
#include <iostream>
#include <string_view>


template <class List, template <class> class MetaFunc, size_t Size = 0>
requires(is_type_list<List>) struct list_to_frozen_map
{
    static constexpr auto value =
        MetaFunc<typename List::current>::retrieve_info(); // get a container;

    static consteval auto make_map()
    {
        return list_to_frozen_map<typename List::next,
                                  MetaFunc,
                                  length<typename List::type>::of>::recurse(value);
    }

    template <typename T, typename... Args>
    static consteval auto recurse(T v, Args... args)
    {
        return list_to_frozen_map<typename List::next, MetaFunc, Size>::recurse(
            value, v, args...);
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
using make_frozen_map = list_to_frozen_map<ListType, MetaFunc, length<ListType>::of>;
