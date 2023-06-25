
#pragma once

#include "plate/definitions.hpp"

#include "core_object/core_object.hpp"

namespace ivd::plate
{

struct PLATE_API margin : public hobject
{
public:
    GENERATE_BODY()

public:
    REFLECT_FIELD(float, left);
    REFLECT_FIELD(float, right);
    REFLECT_FIELD(float, top);
    REFLECT_FIELD(float, bottom);
};

} // namespace ivd::plate