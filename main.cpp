
#include "meta_types/type_list.hpp"
#include <string>
#include <iostream>
#include <tuple>
#include "frozen/unordered_map.h"
#include "reflection/function.hpp"

class T0
{
public:
    static consteval std::pair<std::string_view, int> GetInfo() { return {name, 0}; }
    static constexpr char const*                      name = "T0";
};
class T1
{
public:
    static consteval std::string_view                 GetName() { return "T1"; }
    static consteval std::pair<std::string_view, int> GetInfo() { return {name, 1}; }
    static constexpr std::string_view                 name = "T1";
};
class T2
{
public:
    static consteval std::pair<std::string_view, int> GetInfo() { return {name, 2}; }
    static constexpr std::string_view                 name = "T2";
};

template <class T>
struct get_info
{
    static consteval std::pair<std::string_view, int> retrieve_info()
    {
        return T::GetInfo();
    }
};

class Test
{
    using ThisType = Test;

    template <class T>
    struct a;

    template <class T>
    struct a;

public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b) { return 0; }
    int add2(int a, int b);

    int add(int a, int b, bool c);

    int mult(int a, int b);

public:
    int arr;
};

// on other file maybe?

template <class T>
struct strip;

template <class... Ts>
struct strip<std::tuple<Ts...>>
{
};

int
main()
{
    using T1           = refl::func_type_t<Test, 0>;
    constexpr auto ptr = refl::ptr_to_function<Test, 0>;
    using L1           = type_list<T1>;

    constexpr int size = refl::count_function<Test>;
    Test          a, b;

    (a.*ptr)(1, 2);

    //    int (Test::*p)(int, int) = &Test::add;

    int Test::*p = &Test::arr;
}
