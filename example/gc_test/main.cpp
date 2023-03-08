
#include "core/core.hpp"
#include <string_view>
#include <iostream>

#include <cstddef>

class HActor : public ivd::hobject
{
public:
    GENERATE_BODY();
    virtual ~HActor() { std::cout << "kill hActor\n"; }
};

class Sample : public ivd::hobject
{
public:
    GENERATE_BODY();

    Sample() { 
        y = new_object<HActor>(this); }

    virtual ~Sample()
    {
        std::cout << "Delete Sample*!!\n";
    }

    REFLECT_FUNCTION(add, int, int);
    int add(int, int) { return 0; }

public:
    REFLECT_FIELD(HActor*, y);
};

class T1 : public ivd::hobject
{
public:
    GENERATE_BODY();

    T1() { z = new_object<HActor>(this); }

    virtual ~T1() { std::cout << "Delete T1*!!\n"; }

    REFLECT_FUNCTION(add, int, int);
    int add(int, int) { return 0; }

public:
    REFLECT_FIELD(HActor*, z);
    REFLECT_FIELD(HActor*, zw);
};

void
test(T1* ptr)
{
    ptr->z = nullptr;
}

int
main()
{

    auto array     = ivd::hobject_array::instance();
    auto collector = ivd::garbage_collector::instance();
    auto* ptr2 = new_object<Sample>(nullptr);
    auto* ptr  = new_object<T1>(nullptr);

    collector->add_to_root(ptr);
    collector->add_to_root(ptr2);
    test(ptr);

    collector->mark_objects();
    collector->sweep_objects();
    std::cout << "sweep end";


    return 0;
}