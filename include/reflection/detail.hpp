
#pragma once

#include <cstddef>

namespace refl
{
namespace detail
{
// initial declaration
template <std::size_t, class, template <std::size_t, class> class>
struct index_impl
{
    static constexpr std::size_t value = 0;
};

template <std::size_t I, class Tag, template <std::size_t, class> class Type>
    requires requires { Type<I, Tag>::name; }
struct index_impl<I, Tag, Type>
{
    static constexpr std::size_t value = 1 + index_impl<I + 1, Tag, Type>::value;
};

template <class Tag, template <std::size_t, class> class Type>
struct index
{
    static constexpr std::size_t value = index_impl<0, Tag, Type>::value;
};

} // namespace detail
template <class T, std::size_t Index>
struct dummy_t
{
};
} // namespace refl
