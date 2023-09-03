
#pragma once

namespace refl
{

enum class efield_type : unsigned int
{
    PRIM                    = 0,
    REFLECTED_PTR           = 1,
    REFLECTED_OBJECT_MAP    = 2,
    REFLECTED_OBJECT_QUEUE  = 3,
    REFLECTED_OBJECT_VECTOR = 4,
    INVALID,
};

} // namespace refl
