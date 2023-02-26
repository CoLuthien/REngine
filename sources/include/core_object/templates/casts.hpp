
#pragma once

#include "concepts.hpp"

template <ivd::hobject_type To, ivd::hobject_type From>
To* cast(From* from);

namespace detail
{

template <ivd::hobject_type To, ivd::hobject_type From>
struct cast_impl_t
{
    static inline To* cast_impl(From* from)
    {
        if (from == nullptr)
        {
            return nullptr;
        }

        return from->template is_a<To>() ? (To*)from : nullptr;
    }
};

} // namespace detail

template <ivd::hobject_type To, ivd::hobject_type From>
To*
cast(From* from)
{
    return detail::cast_impl_t<To, From>::cast_impl(from);
}
