
#pragma once
#include "reflection/class.hpp"

inline void this_type_();
class Test : public Base
{
    REGISTER_CLASS();

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
};