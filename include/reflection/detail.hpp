
#pragma once

#include <cstddef>

namespace refl
{
namespace detail
{
// initial declaration
template <size_t, class, template <size_t, class> class>
struct index_impl
{
    static constexpr size_t value = 0;
};

template <size_t I, class Tag, template <size_t, class> class Type>
requires requires { Type<I, Tag>::name; }
struct index_impl<I, Tag, Type>
{
    static constexpr size_t value = 1 + index_impl<I + 1, Tag, Type>::value;
};

template <class Tag, template <size_t, class> class Type>
struct index
{
    static constexpr size_t value = index_impl<0, Tag, Type>::value;
};

} // namespace detail
} // namespace refl