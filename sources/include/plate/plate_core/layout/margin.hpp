
#pragma once

#include "plate/definitions.hpp"

#include "core_object/core_object.hpp"

namespace ivd::plate
{

struct PLATE_API margin
{
    GENERATE_STRUCT()
public:
    margin() = default;
    margin(float in_left, float in_right, float in_top, float in_bottom)
        : left(in_left), right(in_right), top(in_top), bottom(in_bottom)
    {
    }

public:
    REFLECT_FIELD(float, left);
    REFLECT_FIELD(float, right);
    REFLECT_FIELD(float, top);
    REFLECT_FIELD(float, bottom);
};

} // namespace ivd::plate