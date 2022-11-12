
#pragma once

#include "type_helper.hpp"
#include "frozen/bits/elsa_std.h"
#include "frozen/unordered_map.h"
#include <cstddef>
#include <string_view>

namespace refl
{

class refl_class_t
{
public:
    using super     = std::void_t<>;
    using this_type = refl_class_t;

private:
};

} // namespace refl
