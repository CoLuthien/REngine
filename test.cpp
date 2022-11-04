
#include "type_list.hpp"
#include "type_list_utils.hpp"
#include <string>
#include <iostream>
#include <tuple>
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

template <class T>
struct get_name
{
    static consteval std::pair<std::string_view, int> action()
    {
        return T::GetInfo();
    }
};

int main()
{
    using L1 = type_list<T1>;
    using L2 = append_type<T0, L1>;

    constexpr auto a = flatten_to_type<L2, get_name>::get();

    // static_assert( not std::is_invocable_v<int(), int> );
    // static_assert( std::is_invocable_r_v<int, int()> );
    // static_assert( not std::is_invocable_r_v<int*, int()> );
    // static_assert( std::is_invocable_r_v<void, void(int), int> );
    // static_assert( not std::is_invocable_r_v<void, void(int), void> );
    // static_assert( not std::is_invocable_r_v<int(*)(), decltype(func2), void> );
}
