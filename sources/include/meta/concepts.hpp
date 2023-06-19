
#pragma once

#include <type_traits>
#include <memory>

namespace meta
{
template <typename T>
struct is_shared_ptr_t : std::false_type
{
};

template <typename T>
struct is_shared_ptr_t<std::shared_ptr<T>> : std::true_type
{
};

template <typename T>
concept is_shared_ptr = is_shared_ptr_t<T>::value_type;
} // namespace meta
