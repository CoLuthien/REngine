
#pragma once

#include <type_traits>
#include <concepts>

namespace ivd
{
class hobject;

template <typename T>
concept hobject_type = std::is_base_of_v<hobject, std::decay_t<T>>;

} // namespace ivd
