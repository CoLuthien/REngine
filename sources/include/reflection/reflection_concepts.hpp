
#pragma once

#include "reflection_utils.hpp"
#include <type_traits>

namespace ivd
{
class hobject;
}

namespace refl
{

template <typename T>
concept is_reflected_type = requires {
                                typename T::template detail_field_reflection<0>;
                                typename T::template detail_function_reflection<0>;
                            };

} // namespace refl
