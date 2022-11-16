
// in C++17
#include "meta_types/type_list.hpp"
#include "reflection/class.hpp"
#include "reflection/property.hpp"
#include "reflection/function.hpp"
#include "frozen/unordered_map.h"
#include <string>
#include <iostream>
#include <tuple>
#include <string_view>

#include <type_traits>

template <class T>
struct get_info
{
    static consteval std::pair<std::string_view, int> retrieve_info()
    {
        return T::GetInfo();
    }
};

class Base
{
public:
    using super     = std::void_t<>;
    using this_type = Base;
};

class Test : public Base
{
public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b);

    REFLECT_FUNCTION(mult, int, int);
    int mult(int, int)
    {
        std::cout << "Real mult!!";
        return 0;
    }

public:
    REFLECT_MEMBER(arr, int);
    REFLECT_MEMBER(arr2, int);
};

class Test2 : public Base
{
public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b);

    int add2(int a, int b, bool c);

    REFLECT_FUNCTION(mult, int);
    int mult(int)
    {
        std::cout << "Real mult!!";
        return 0;
    }

public:
    REFLECT_MEMBER(arr, int);
    REFLECT_MEMBER(arr2, int);
};

int
Test::add(int a, int b)
{

    std::cout << "Real Add Test!!";

    arr += (a + b);
    arr2 = (arr / 2);
    return a + b;
}

int
Test2::add(int a, int b)
{

    std::cout << "Real Add Test2!!";

    arr += (a + b);
    return a + b;
}

static constexpr auto f1 = refl::refl_func_t(refl::dummy_t<Test, 0>{});
static constexpr auto fn = refl::
    to_frozen_map<refl::function_info, Test, refl::count_functions<Test>>::make_map();

void
test(decltype(f1)& p, void* object)
{
    p.invoke<int>(object, 1, 2);
}

// on other file maybe?

constexpr auto clazz = refl::refl_object_t::make_reflection<Test>();

int
main()
{

    Test* c  = new Test;
    Test2* d = new Test2;

    static_assert(refl::count_functions<Test> == 2);
    static_assert(refl::count_properties<Test> == 2);

    auto f2 = refl::refl_func_t(refl::dummy_t<Test2, 0>{});

    auto p1 = refl::refl_prop_t(refl::dummy_t<Test, 0>{});

    int Test::*ptr = &Test::arr;

    using type = int Test::*;

    auto pair = clazz.get_function("add");
    auto prop_pair = clazz.get_property("arr");

    pair->second.invoke<int>(c, 1, 3);
    std::cout << prop_pair->second.get<int>(c) << '\n';
    pair->second.invoke<int>(c, 1, 3);
    std::cout << prop_pair->second.get<int>(c) << '\n';
    std::cout << c->arr;
}
