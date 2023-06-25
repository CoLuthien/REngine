
#pragma once

#include "plate/definitions.hpp"

#include "plate_render/drawable_description.hpp"
#include "plate_render/drawable_layout.hpp"

namespace ivd::plate
{

class PLATE_API drawable_description_factory
{
    static void make_box_description(drawable_description_list& list,
                                     std::size_t                layer_id,
                                     layout_geometry            geometry // geometry
                                                                         // color todo
    );
};

} // namespace ivd::plate