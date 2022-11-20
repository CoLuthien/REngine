
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

class Test
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

int
Test::add(int a, int b)
{

    std::cout << "Real Add Test!!";

    arr += (a + b);
    arr2 = (arr / 2);
    return a + b;
}

// on other file maybe?

constexpr auto clazz = refl::refl_class_t::make_reflection<Test>();

int
main()
{

    Test* c = new Test;

    auto pair      = clazz.get_function("add");
    auto prop_pair = clazz.get_property("arr");

    pair->second.invoke<int>(c, 1, 2, 3, 4);
    std::cout << prop_pair->second.get<int>(c) << '\n';
    pair->second.invoke<int>(c, 1, 3);
    std::cout << prop_pair->second.get<int>(c) << '\n';
    std::cout << c->arr;
}
