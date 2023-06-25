
#pragma once

#include "math/color.hpp"

#include "plate/definitions.hpp"
#include "plate_render/drawable_description.hpp"
#include "plate_render/drawable_layout.hpp"

namespace ivd::plate
{

class PLATE_API drawable_description_factory
{
public:
    static void make_box_description(drawable_description_list& list,
                                     std::size_t                layer_id,
                                     layout_geometry            in_geometry, // geometry
                                     color                      in_color);
};

} // namespace ivd::plate