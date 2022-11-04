
#include "type_list.hpp"
#include "type_list_utils.hpp"
#include <string>
#include <iostream>
#include <tuple>
#include "type_helper.hpp"
#include "frozen/unordered_map.h"

class T0
{
public:
    static consteval std::pair<std::string_view, int> GetInfo()
    {
        return {name, 0};
    }
    static constexpr char const *name = "T0";
};
class T1
{
public:
    static consteval std::string_view GetName()
    {
        return "T1";
    }
    static consteval std::pair<std::string_view, int> GetInfo()
    {
        return {name, 1};
    }
    static constexpr std::string_view name = "T1";
};
class T2
{
public:
    static consteval std::pair<std::string_view, int> GetInfo()
    {
        return {name, 2};
    }
    static constexpr std::string_view name = "T2";
};

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
public:
    int add(int a, int b);
    int add(int a, int b, bool c);
};

int main()
{
    using L1 = type_list<T1>;
    using L2 = append_type<T0, L1>;
    using L3 = append_type<T2, L2>;

    Test a, b;

    int (Test::* p)(int, int) = &Test::add;
    std:: cout << p << '\n';


}
