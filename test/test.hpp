
#pragma once
#include "GObject/GObject.hpp"
#include <Reflection/Reflection.hpp>

class U : public ge::GObject
{
public:
};

class Test : public ge::GObject
{
    REFLECT_CLASS();

    Test()
    {
        arr = 12;
        arr2 = 13;
    }

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
    REFLECT_MEMBER(int, arr);
    REFLECT_MEMBER(int, arr2);
    REFLECT_MEMBER(U, us);
};