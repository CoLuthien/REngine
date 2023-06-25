
#pragma once

#include "plate/definitions.hpp"
#include "math/vector.hpp"
#include "math/extent.hpp"

namespace ivd::plate
{

class PLATE_API layout_transform
{
public:
private:
    float    scale;
    point2_f translation;
};

/*
Assume that all the element layout anchored to upper left corner
 */

class PLATE_API layout_geometry
{
public:
    layout_geometry organize_element(extent2_f offset, extent2_f size, float scale);

private:
    layout_transform from_parent;
    extent2_f        local_size;
};

} // namespace ivd::plate