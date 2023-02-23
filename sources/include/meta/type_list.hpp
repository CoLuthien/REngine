
#pragma once

#include <type_traits>

namespace meta
{

template <typename... Ts>
struct typelist;

using null_list = typelist<std::nullptr_t>;

template <typename T>
struct typelist<T>
{
    using type    = typelist<T>;
    using next    = null_list;
    using current = T;
};

template <class T, class... Rs>
struct typelist<T, Rs...>
{
    using type    = typelist<T, Rs...>;
    using next    = typelist<Rs...>;
    using current = T;
};

namespace list
{

template <typename List>
struct size_of_t;

template <typename... Ts>
struct size_of_t<typelist<Ts...>>
{
    static constexpr auto length = 1 + size_of_t<typename typelist<Ts...>::next>::length;
};

template <>
struct size_of_t<null_list>
{
    static constexpr auto length = 0;
};

template <class List, class F>
struct for_each_t
{
    static constexpr void apply()
    {
        F::template action<List::current>();
        for_each_t<typename List::next, F>::apply();
    }
};

template <class F>
struct for_each_t<null_list, F>
{
    static constexpr void apply() { return; }
};

template <class List>
constexpr auto size = size_of_t<List>::length;

template <class List, class T>
struct push_front_t;

template <class... Elems, class T>
struct push_front_t<typelist<Elems...>, T>
{
    using result = typelist<T, Elems...>;
};

template <class List>
struct pop_front_t;

template <class... Es>
struct pop_front_t<typelist<Es...>>
{
    using result = typename typelist<Es...>::next;
};

template <class List, class T>
struct push_back_t;

template <class... Elems, class T>
struct push_back_t<typelist<Elems...>, T>
{
    using result = typelist<Elems..., T>;
};

template <typename T, typename U>
struct merge_list_t;

template <typename... Ts, typename... Us>
struct merge_list_t<typelist<Ts...>, typelist<Us...>>
{
    using result = typelist<Ts..., Us...>;
};

template <class List, class T>
using push_front = typename push_front_t<List, T>::result;
template <class List>
using pop_front = typename pop_front_t<List>::result;
template <class List, class T>
using push_back = typename push_back_t<List, T>::result;
template <typename T, typename U>
using merge = typename merge_list_t<T, U>::result;

} // namespace list

} // namespace meta