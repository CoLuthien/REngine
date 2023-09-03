
#pragma once

#include "math/color.hpp"

#include "plate_export.hpp"
#include "plate_render/drawable_description.hpp"
#include "plate_render/drawable_layout.hpp"
#include "plate_core/layout/margin.hpp"

namespace ivd::plate
{

class PLATE_API drawable_description_factory
{
public:
    static void make_box_description(drawable_description_list& list,
                                     std::size_t                layer_id,
                                     layout_geometry            in_geometry,
                                     color                      in_color,
                                     margin                     in_margin);
};

} // namespace ivd::plate