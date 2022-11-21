
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

class Base
{
public:
    using this_type = Base;
};

class Test : public Base
{
public:
    DECLARE_TYPE();
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b);

    REFLECT_FUNCTION(mult, int, int);
    int mult(int, int)
    {
        std::cout << "Real mult!!";
        return 0;
    }

public:
    REFLECT_MEMBER(int, arr);
    REFLECT_MEMBER(int, arr2);
};

int
Test::add(int a, int b)
{

    std::cout << "Real Add Test!!";

    arr += (a + b);
    arr2 = (arr / 2);
    return a + b;
}

// on other file maybe?

int
main()
{
    constexpr auto clazz = refl::refl_class_t::make_reflection<Test>();
    auto cl              = clazz;

    Test* c = new Test;

    auto pair      = cl.get_function("add");
    auto prop_pair = cl.get_property("arr");


    pair->second.invoke<int>(c, 1, 3, 4, 5);
    std::cout << prop_pair->second.get<int>(c) << '\n';
    pair->second.invoke<int>(c, 1, 3);
    std::cout << prop_pair->second.get<int>(c) << '\n';
    std::cout << c->arr;
}
