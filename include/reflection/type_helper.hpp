
#pragma once
#include "detail.hpp"
#include <type_traits>

namespace refl
{
namespace type_helper
{
template <typename T>
struct this_type_reader
{
    friend auto this_type(this_type_reader<T>);
};

template <typename T, typename U>
struct this_type_writer
{
    friend auto this_type(this_type_reader<T>) { return U{}; }
};

inline void this_type();

template <typename T>
using this_type_read = std::remove_pointer_t<decltype(this_type(this_type_reader<T>{}))>;

} // namespace type_helper

template <class Target, std::size_t I>
using refl_func_info =
    typename Target::template detail_function_reflection<I, struct detail_function_tag>;

template <class Target, std::size_t I>
constexpr auto func_name_v = refl_func_info<Target, I>::name;

template <class Target, std::size_t I>
using func_type_t = typename refl_func_info<Target, I>::template type<Target>;

template <class Target, std::size_t I>
constexpr auto func_ptr_v = refl_func_info<Target, I>::template offset_v<Target>;

template <class Target>
constexpr std::size_t count_functions =
    detail::index<struct function_counter_tag,
                  Target::template detail_function_reflection>::value;

template <class Target, std::size_t I>
using refl_prop_info =
    typename Target::template detail_property_reflection<I, struct detail_member_tag>;

template <class Target, size_t I>
constexpr auto prop_name_v = refl_prop_info<Target, I>::name;

template <class Target, size_t I>
using prop_type_t = typename refl_prop_info<Target, I>::type;

template <class Target, size_t I>
using prop_ptr_type_t = typename refl_prop_info<Target, I>::template ptr_type<Target>;

template <class Target, std::size_t I>
constexpr auto prop_ptr_v = refl_prop_info<Target, I>::template offset_v<Target>;

template <class Target>
constexpr size_t count_properties =
    detail::index<struct property_counter_tag,
                  Target::template detail_property_reflection>::value;

} // namespace refl

#define DECLARE_TYPE()                                                                   \
public:                                                                                  \
    constexpr auto this_type_helper()                                                    \
        ->decltype(refl::type_helper::this_type_writer<struct this_type_tag,             \
                                                       decltype(this)>{},                \
                   void());                                                              \
    using super     = this_type;                                                         \
    using this_type = refl::type_helper::this_type_read<struct this_type_tag>;
