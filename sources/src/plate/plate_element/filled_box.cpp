

#include "plate_element/filled_box.hpp"
#include "plate_render/drawable_description_factory.hpp"

namespace ivd::plate
{

filled_box::filled_box()  = default;
filled_box::~filled_box() = default;

void
filled_box::draw(drawable_description_list& list,
                 std::size_t                layer_id,
                 layout_geometry const&     geometry)
{
    // todo

    drawable_description_factory::make_box_description(
        list, layer_id, geometry.organize_element(0, {}, 1), {});
}

} // namespace ivd::plate