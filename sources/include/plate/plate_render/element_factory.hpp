
#pragma once

#include "plate/definitions.hpp"

#include "plate_render/element.hpp"
#include "plate_render/element_layout.hpp"

namespace ivd::plate
{

class PLATE_API element_factory
{
    static void make_box(element_list&   list,
                            std::size_t     layer,
                            layout_geometry geometry // geometry
                                                     // color todo
    );
};

} // namespace ivd::plate