
#include "core_object/class.hpp"
#include <string_view>
#include <iostream>

#include <cstddef>

class T1 : public ivd::hobject_t
{
public:
    GENERATE_BODY()

};

class T2 : public ivd::hobject_t
{
public:
    GENERATE_BODY()

};

class Sample : public ivd::hobject_t
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

private:
    REFLECT_FIELD(int const, x);
    REFLECT_FIELD(int const, y);
    REFLECT_FIELD(int const, z);
    REFLECT_FIELD(int, w);
};

int
main()
{

    auto* ptr = new Sample{};
    // ptr->x = ptr->y = ptr->z = 12; # error!
    auto* ptr2 = new Sample{};

    auto* clazz = Sample::static_class();

    std::cout << ptr->is_a(ptr2) << '\n';

    // auto z = ptr->z;

    auto func_add = clazz->find_func("add");

    if (func_add != nullptr)
    {
        int x = func_add->invoke<int>(ptr, 1, 2);
    }

    auto prop_x = clazz->find_field("x");
    if (prop_x != nullptr)
    {
        std::cout << "field name: x found, value is: " << prop_x->get<int>(ptr) << '\n';

        std::cout << "field name: x, try set value as: 12\n";
        prop_x->set<int>(ptr, 12);

        std::cout << "field name: x, setted value is: " << prop_x->get<int>(ptr) << '\n';
    }

    auto prop_w = clazz->find_field("w");
    if (prop_w != nullptr)
    {
        std::cout << "field name: w found, value is: " << prop_x->get<int>(ptr) << '\n';

        std::cout << "field name: w, try set value as: 12\n";
        prop_w->set<int>(ptr, 12);

        std::cout << "field name: w, setted value is: " << prop_w->get<int>(ptr) << '\n';
    }

    return 0;
}