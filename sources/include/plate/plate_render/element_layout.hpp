
#pragma once

#include "plate/definitions.hpp"

#include "math/point.hpp"
#include "math/vector.hpp"
#include "math/extent.hpp"

namespace ivd::plate
{

class layout_transform
{
public:
private:
    float    scale;
    point2_f translation;
};

/*
Assume that all the element layout anchored to upper left corner
 */

class layout_geometry
{
public:
private:
    layout_transform from_parent;
    extent2_f        local_size;
};

} // namespace ivd::plate