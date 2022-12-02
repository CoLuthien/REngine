
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

    arr += (a + b);
    arr2 = (arr / 2);
    return a + b;
}

class T
{
    T()
    {
        arr = new int[12];
        ptr = new Test{};
    }
    private: 
        int* arr;
        Test* ptr;
};

// on other file maybe?

int
main()
{
    auto clazz = Test::reflected_class();
    auto cl    = clazz;

    std::cout << sizeof(T);
}
