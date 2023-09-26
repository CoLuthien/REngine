
#pragma once

#include "meta/type_traits.hpp"

namespace meta
{

template <typename T, typename U>
    requires requires { typename U::MaskType; }
static constexpr auto
mask_as_enum(U value)
{
    return static_cast<T>(typename U::MaskType(value));
}

template <typename T, typename U>
    requires requires { typename U::MaskType; }
static constexpr auto
mask_from_flags(U flags)
{
    return static_cast<T>(typename U::MaskType(flags));
}

} // namespace meta