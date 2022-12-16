
#pragma once

#include "reflection_utils.hpp"
#include <type_traits>

namespace hln
{
class hobject_t;
}

namespace refl
{

template <typename T>
concept is_property_reflected = requires { T::template detail_field_reflection; };

template <typename T>
concept is_iterable_type = requires {
                               typename T::iterator;
                               typename T::const_iterator;
                           };

template <typename T>
concept is_supported_iterable =
    requires {
        std::is_base_of_v<hln::hobject_t, std::decay_t<typename T::value_type>>&&
            is_iterable_type<T>;
    };

} // namespace refl
