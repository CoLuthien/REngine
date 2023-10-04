
#pragma once

#include "utils/non_copyable.hpp"

#include <string>
#include <string_view>
#include <memory>

namespace ivd::rdi
{
#ifdef USE_VALIDATION_LAYER
static constexpr bool NEED_VALIDATION_LAYER = true;
#else
static constexpr bool NEED_VALIDATION_LAYER = false;
#endif

} // namespace ivd::rdi
