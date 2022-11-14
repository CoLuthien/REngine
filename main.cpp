
#include "meta_types/type_list.hpp"
#include "reflection/function.hpp"
#include "reflection/member.hpp"
#include "reflection/class.hpp"
#include "frozen/unordered_map.h"
#include <string>
#include <iostream>
#include <tuple>

template <class T>
struct get_info
{
    static consteval std::pair<std::string_view, int> retrieve_info()
    {
        return T::GetInfo();
    }
};
#include <type_traits>

class Base
{
public:
    using super     = std::void_t<>;
    using this_type = Base;
};

class Test : public Base
{
public:
public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b);

    int add2(int a, int b, bool c);

    REFLECT_FUNCTION(mult, int);
    int mult(int)
    {
        std::cout << "Real mult!!";
        return 0;
    }

public:
    REFLECT_MEMBER(arr, int);
    REFLECT_MEMBER(arr2, int);
};

int
Test::add(int a, int b)
{

    std::cout << "Real Add!!";

    arr += (a + b);
    return a + b;
}

class T
{
public:
    constexpr T() = default;
    virtual void test(){};
};
static constexpr auto f1 = refl::refl_func_t(refl::dummy_t<Test, 0>{});

void
test(decltype(f1)& p, void* object)
{
    p.Invoke<int>(object, 1, 2);
}

// on other file maybe?

int
main()
{
    constexpr auto var = T{};

    Test* c = new Test;
    Test* d = new Test;

    auto f2 = refl::refl_func_t(refl::dummy_t<Test, 0>{});

    int (Test::*p)(int, int) = &Test::add;
    std::cout << f1.Invoke<int>(c, 1, 12);
    std::cout << c->arr << '\n';
    test(f1, c);
    std::cout << c->arr << '\n';

    auto value = f1.Invoke<int>(c, 1, 13);
}
