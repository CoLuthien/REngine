
// in C++17
#include "test.hpp"
#include "frozen/unordered_map.h"
#include <Reflection/Reflection.hpp>
#include <string>
#include <iostream>
#include <tuple>
#include <string_view>
#include <memory>

#include <type_traits>

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
    auto clazz = Test::reflected_class();
    auto cl    = clazz;
    Test* c    = ge::make_reflected<Test>();

    ge::GObject* ptr = c;
    c                  = nullptr;

    auto pair = cl->get_function("add");
    auto prop = cl->get_property("arr");
    auto us   = cl->get_property("us");

    pair.invoke<int>(ptr, 1, 3);
    std::cout << prop.get<int>(ptr) << '\n';
    pair.invoke<int>(ptr, 1, 3);
    std::cout << prop.get<int>(ptr) << '\n';
}
