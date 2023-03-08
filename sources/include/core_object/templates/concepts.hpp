
#pragma once

#include <type_traits>
#include <concepts>

namespace ivd
{

template <typename T>
concept hobject_type = std::is_base_of_v<class hobject, std::decay_t<T>>;

} // namespace ivd
