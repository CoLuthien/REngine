
#include "meta_types/type_list.hpp"
#include "reflection/function.hpp"
#include "reflection/member.hpp"
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

class Test
{

    template <class T>
    struct a;

    template <class T>
    struct a;

public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b)
    {
        std::cout << "Hello Invoke";
        return 0;
    }
    int add2(int a, int b);

    int add(int a, int b, bool c);

    int mult(int a, int b);

public:
    REFLECT_MEMBER(arr, int);
};

// on other file maybe?

int
main()
{

    constexpr int size = refl::count_function<Test>;
    Test a, b;

    Test* c = new Test;

    int (Test::*p)(int, int) = &Test::add;

    using ftype = refl::func_type_t<Test, 0>;

    strip_and_apply<ftype, method_traits<ftype>::args_type>::func(p, *c, 1, 2);
}
