
#pragma once

#include "meta/utils.hpp"
#include "reflection_utils.hpp"
#include <type_traits>

#include <vector>
#include <queue>
#include <unordered_map>

namespace refl
{

template <typename T>
using has_reflected_field_t = typename T::template detail_field_reflection<0>;

template <typename T>
using has_reflected_function_t = typename T::template detail_function_reflection<0>;

template <typename T>
concept is_reflected_type = requires {
    typename has_reflected_field_t<typename meta::remove_all_qualifiers_t<T>>;
    typename has_reflected_function_t<typename meta::remove_all_qualifiers_t<T>>;
};
template <typename T>
concept is_reflected_object_queue =
    meta::is_specialization<T, std::queue> &&
    is_reflected_type<typename meta::remove_all_qualifiers_t<T>::value_type> &&
    std::is_pointer_v<typename meta::remove_all_qualifiers_t<T>::value_type>;

template <typename T>
concept is_reflected_object_vector =
    meta::is_specialization<T, std::vector> &&
    is_reflected_type<typename meta::remove_all_qualifiers_t<T>::value_type> &&
    std::is_pointer_v<typename meta::remove_all_qualifiers_t<T>::value_type>;

template <typename T>
concept is_reflected_object_map =
    meta::is_specialization<T, std::unordered_map> &&
    is_reflected_type<typename meta::remove_all_qualifiers_t<T>::mapped_type> &&
    std::is_pointer_v<typename meta::remove_all_qualifiers_t<T>::mapped_type>;

template <typename T>
concept is_fundamental_queue =
    meta::is_specialization<T, std::queue> &&
    std::is_fundamental_v<typename meta::remove_all_qualifiers_t<T>::value_type> &&
    (std::is_pointer_v<typename meta::remove_all_qualifiers_t<T>::value_type> == false);

template <typename T>
concept is_fundamental_vector =
    meta::is_specialization<T, std::vector> &&
    std::is_fundamental_v<typename meta::remove_all_qualifiers_t<T>::value_type> &&
    (std::is_pointer_v<typename meta::remove_all_qualifiers_t<T>::value_type> == false);
template <typename T>
concept is_fundamental_map =
    meta::is_specialization<T, std::unordered_map> &&
    std::is_fundamental_v<typename meta::remove_all_qualifiers_t<T>::mapped_type> &&
    (std::is_pointer_v<typename meta::remove_all_qualifiers_t<T>::mapped_type> == false);

} // namespace refl
