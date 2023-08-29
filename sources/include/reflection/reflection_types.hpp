
#pragma once

namespace refl
{

enum class efield_type : unsigned int
{
    PRIM                       = 0,
    REGULAR                    = 1,
    REFLECTED                  = 2,
    REFLECTED_PTR              = 3,
    REFLECTED_OBJECT_CONTAINER = 4,
    INVALID,
};

} // namespace refl
