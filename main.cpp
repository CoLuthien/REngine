
                                       // in C++17
#include "meta_types/type_list.hpp"
#include "reflection/function.hpp"
#include "reflection/member.hpp"
#include "reflection/class.hpp"
#include "frozen/unordered_map.h"
#include <string>
#include <iostream>
#include <tuple>
#include <string_view>

#include <type_traits>

template <class T>
struct get_info
{
    static consteval std::pair<std::string_view, int> retrieve_info()
    {
        return T::GetInfo();
    }
};

class Base
{
public:
    using super     = std::void_t<>;
    using this_type = Base;
};

class Test : public Base
{
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

class Test2 : public Base
{
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

    std::cout << "Real Add Test!!";

    arr += (a + b);
    arr2 = (arr / 2);
    return a + b;
}

int
Test2::add(int a, int b)
{

    std::cout << "Real Add Test2!!";

    arr += (a + b);
    return a + b;
}

static constexpr auto f1 = refl::refl_func_t(refl::dummy_t<Test, 0>{});


void
test(decltype(f1)& p, void* object)
{
    p.invoke<int>(object, 1, 2);
}

// on other file maybe?

int
main()
{

    Test* c  = new Test;
    Test2* d = new Test2;

    static_assert(refl::count_functions<Test> == 2);
    static_assert(refl::count_properties<Test> == 2);

    auto f2 = refl::refl_func_t(refl::dummy_t<Test2, 0>{});

    auto p1 = refl::refl_prop_t(refl::dummy_t<Test, 0>{});
    #ifdef __clang__
    std::cout << "clang";
    #endif

    int Test::*ptr = &Test::arr;

    using type = int Test::*;

    int (Test::*p)(int, int) = &Test::add;
    std::cout << f1.invoke<int>(c, 1, 18);

}
