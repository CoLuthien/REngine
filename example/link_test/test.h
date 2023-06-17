

#pragma once

#include "test.h"
#include "core/core.hpp"
#include "core_object/core_object.hpp"

class T1 : public ivd::hobject
{
public:
    GENERATE_BODY();
    virtual ~T1() = default;
};

class Sample : public T1
{
public:
    GENERATE_BODY();
    virtual ~Sample() = default;

public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b)
    {
        return a + b;
    }

private:
    REFLECT_FIELD(int const, x);
    REFLECT_FIELD(int const, y);
    REFLECT_FIELD(int const, z);
    REFLECT_FIELD(int, w);
};

class T3 : public Sample
{
    GENERATE_BODY();
};

T1* get_object();