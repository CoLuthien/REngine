
#pragma once

#include "HAL/attributes.hpp"
#include <cstddef>

namespace ivd
{

using object_flag = uint64_t;
namespace eobject_flag
{
constexpr uint64_t UNREACHABLE  = 1 << 0;
constexpr uint64_t PENDING_KILL = 1 << 1;
constexpr uint64_t ROOT_OBJECT  = 1 << 2;
}; // namespace eobject_flag
} // namespace ivd
