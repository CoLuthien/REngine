
#include "drawable_factory.hpp"

#include "plate_render/drawable_info.hpp"
#include "math/transforms.hpp"

namespace ivd::plate
{

drawable
drawable_factory::make_filled_box(drawable_description const& desc)
{
    // adding vertex and etc... actual triangle and color setup happens in here

    auto info = desc.get_info<filled_box_drawable_info>();

    drawable result;
    // make 2 triangles
    auto      offset        = desc.get_size();
    auto      location      = desc.get_location();
    extent2_f offset_right  = offset;
    extent2_f offset_bottom = offset;

    offset_right.y             = 0;
    offset_bottom.x            = 0;
    drawable_index index_start = 0;

    // upper left
    result.add_vertex(drawable_vertex{.position = location});
    // upper right
    result.add_vertex(drawable_vertex{.position = ivd::translate(location, offset_right)});
    // lower left
    result.add_vertex(drawable_vertex{.position = ivd::translate(location, offset_bottom)});
    //  lower right
    result.add_vertex(drawable_vertex{.position = ivd::translate(location, offset)});

    // first triable
    result.add_index(index_start);
    result.add_index(index_start + 1);
    result.add_index(index_start + 2);

    // second triangle
    result.add_index(index_start + 1);
    result.add_index(index_start + 2);
    result.add_index(index_start + 3);

    return result;
}

} // namespace ivd::plate