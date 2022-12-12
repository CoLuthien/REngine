
#pragma once

#include "reflection_utils.hpp"

namespace refl
{

template <typename T>
concept is_property_reflected = requires
{
    T::template detail_property_reflection;
};

} // namespace refl
