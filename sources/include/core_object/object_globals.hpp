
#pragma once

#include <cstddef>
#include <cstdint>

namespace ivd
{

using object_flag = std::uint64_t;
namespace eobject_flag
{
static constexpr uint64_t UNREACHABLE  = 1 << 0;
static constexpr uint64_t PENDING_KILL = 1 << 1;
static constexpr uint64_t ROOT_OBJECT  = 1 << 2;
}; // namespace eobject_flag
} // namespace ivd
