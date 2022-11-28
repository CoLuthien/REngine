
#pragma once
#include <reflection/reflection.hpp>



class Test : public refl_object_t
{
    REFLECT_CLASS();

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