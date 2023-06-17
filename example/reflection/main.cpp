
#include "core/core.hpp"
#include "core_object/core_object.hpp"
#include <string_view>
#include <iostream>

class Sample : public ivd::hobject
{
public:
    GENERATE_BODY();

public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b)
    {
        std::cout << "add " << a << " and " << b << '\n';
        return a + b;
    }

public:
    REFLECT_FIELD(int, x);
    REFLECT_FIELD(int, w);
};

class Test : public Sample 
{
public:
    GENERATE_BODY();

};

class Test2 : public Test
{
public:
    GENERATE_BODY();

};

int
main()
{
    auto* ptr   = new_object<Sample>(nullptr);
    auto* clazz = Sample::static_class();

    auto func_add = clazz->find_func("add");

    if (func_add != nullptr)
    {
        int x = func_add->invoke<int>(ptr, 1, 2);
        std::cout << x << '\n';
    }

    ptr->w = 0;

    auto prop_w = clazz->find_field("w");
    if (prop_w != nullptr)
    {
        int value = prop_w->get<int>(ptr); // 0
        prop_w->set<int>(ptr, 12);         // set to 12
        value = prop_w->get<int>(ptr);     // 12
        std::cout << value << '\n';
    }

    return 0;
}