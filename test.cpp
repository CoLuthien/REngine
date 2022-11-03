
#include "type_list.hpp"
#include "type_list_utils.hpp"
#include <type_traits>
#include <string>
#include <iostream>

class T0
{
public:
    static constexpr std::string_view GetName()
    {
        return "T0";
    }
};
class T1
{
public:
    static constexpr std::string_view GetName()
    {
        return "T1";
    }
};
class T2
{
public:
    static constexpr std::string_view GetName()
    {
        return "T2";
    }
};

template< class T>
struct get_name
{
    static consteval std::string_view action()
    {
        return T::GetName();
    }
};

int func(int a, int b, int c)
{
    return 0;
}

auto func2(char) -> int (*)()
{
    return nullptr;
}

int main()
{
    using L1 = type_list<T0, T1, T2>;


    auto list = flatten_to_type<L1, get_name>::get();



    static_assert(std::is_invocable_v<int()>);
    constexpr auto p1 = std::pair(std::string_view("12"), 12);
    constexpr auto p2 = std::pair(std::string_view("13"), 13);

    // static_assert( not std::is_invocable_v<int(), int> );
    // static_assert( std::is_invocable_r_v<int, int()> );
    // static_assert( not std::is_invocable_r_v<int*, int()> );
    // static_assert( std::is_invocable_r_v<void, void(int), int> );
    // static_assert( not std::is_invocable_r_v<void, void(int), void> );
    // static_assert( not std::is_invocable_r_v<int(*)(), decltype(func2), void> );
}
