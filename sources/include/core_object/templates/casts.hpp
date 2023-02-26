
#pragma once

#include "concepts.hpp"

template <typename To, typename From>
To* cast(From* from);

namespace detail
{

template <typename To, typename From>
struct cast_impl_t
{
    static inline To* cast_impl(From* from)
    {
        return from->template is_a<To>() ? (To*)from : nullptr;
    }
};

} // namespace detail

template <typename To, typename From>
To*
cast(From* from)
{
    return detail::cast_impl_t<To, From>::cast_impl(from);
}
