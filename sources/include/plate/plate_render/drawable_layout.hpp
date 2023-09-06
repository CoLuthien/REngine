
#pragma once

#include "plate_export.hpp"
#include "math/vector.hpp"
#include "math/extent.hpp"
#include "math/transforms.hpp"

namespace ivd::plate
{

class PLATE_API layout_transform
{
public:
    explicit layout_transform(point2f in_offset) : offset(in_offset) {}
    explicit layout_transform(point2f in_offset, float in_scale)
        : scale(in_scale), offset(in_offset)
    {
    }
    explicit layout_transform(float in_scale = 1.f) : scale(in_scale) {}

    point2f translate(point2f const& original) const
    {
        return ivd::translate(original, as_extent(offset));
    }

private:
    float    scale;
    point2f offset;
};

/*
Assume that all the element layout anchored to upper left corner
 */

class PLATE_API layout_geometry
{
public:
    layout_geometry organize_element(point2f location, extent2_f size, float scale) const
    {
        layout_geometry result;
        result.from_parent = layout_transform(from_parent.translate(location), scale);
        result.local_size  = size;
        return result;
    }

    point2f  get_location() const { return from_parent.translate(location); }
    extent2_f get_size() const { return local_size; }

private:
    layout_transform from_parent;
    point2f         location;
    extent2_f        local_size;
};

} // namespace ivd::plate