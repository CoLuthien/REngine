
#include "core/core.hpp"
#include "core_object/core_object.hpp"
#include "math/vector.hpp"
#include "math/point.hpp"
#include "math/quaternion.hpp"
#include <string_view>
#include <iostream>
#include <unordered_map>
#include <meta/utils.hpp>

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

template <typename T>
class Test2 : public Test
{
public:
    GENERATE_BODY();

public:
    REFLECT_FIELD(std::vector<T>, Type);
    REFLECT_FIELD(std::queue<T>, queue);
    REFLECT_FIELD(std::unordered_map<DECLARE_TEMPLATE_PARAMS(std::string, T)>, map);
};

int
main()
{
    using TType = ivd::hobject*;
    auto* ptr   = new_object<Test2<TType>>(nullptr);
    auto* clazz = Test2<TType>::static_class();

    ivd::vector3d v(3);
    auto*         d = v.static_struct();

    if (auto* my_x = d->find_field("x"))
    {
        return 0;
    }

    auto func_add = clazz->find_func("add");

    if (func_add != nullptr)
    {
        int x = func_add->invoke<int>(ptr, 1, 2);
        std::cout << x << '\n';
    }

    auto prop_w = clazz->find_field("Type");
    if (prop_w != nullptr)
    {
        auto& value = prop_w->get<std::vector<TType>>(ptr); // 0
    }
    std::cout << meta::to_underlying(prop_w->get_type());

    return 0;
}