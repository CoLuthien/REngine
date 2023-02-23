
#pragma once

#include <type_traits>

namespace ivd
{

template <typename T>
concept is_hobject = std::is_base_of_v<class hobject_t, std::decay_t<T>>;

} // namespace ivd
