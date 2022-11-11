
#pragma once

#include <type_traits>

// https://lacti.github.io/2014/06/29/variadic-template-typelist/

template <typename... Ts>
struct type_list;

using null_type_list = type_list<std::nullptr_t>;

template <typename T>
struct type_list<T>
{
    using type = type_list<T>;
    using next = null_type_list;
    using current = T;
    struct list_tag;
};

template <class T, class... Rs>
struct type_list<T, Rs...>
{
    using type = type_list<T, Rs...>;
    using next = type_list<Rs...>;
    using current = T;
    struct list_tag;
};

template <typename T>
concept is_type_list = requires
{
    typename T::list_tag;
};

// https://stackoverflow.com/questions/16648144/merge-two-variadic-templates-in-one 참고
template <class T, class U>
struct append_type_to_list;

template <class T, typename... Us>
struct append_type_to_list<T, type_list<Us...>>
{
    using type = type_list<T, Us...>;
};

template <typename T, class U>
requires(!is_type_list<T>) // 약간 비 직관적임.. :(
    using append_type = typename append_type_to_list<T, U>::type;

template <class T, class U>
struct merge_type_list;

template <class... Ts, class... Us>
struct merge_type_list<type_list<Ts...>, type_list<Us...>>
{
    using type = type_list<Ts..., Us...>;
};

template <typename T, class U>
using merge_list = typename merge_type_list<T, U>::type;

template <typename List>
struct length
{
    static constexpr std::size_t of = 1 + length<typename List::next>::of;
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
    static consteval void visit() {}
};
