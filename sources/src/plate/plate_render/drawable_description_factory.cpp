
#include "plate_render/drawable_description_factory.hpp"
#include "plate_render/drawable_info.hpp"

#include <memory>

namespace ivd::plate
{

void
drawable_description_factory::make_box_description(drawable_description_list& list,
                                                   std::size_t                layer,
                                                   layout_geometry            geometry,
                                                   color                      in_color)
{
    drawable_description desc;

    desc.initialize(drawable_type_e::BOX,
                    std::make_unique<drawable_info>(),
                    geometry.get_location(),
                    geometry.get_size(),
                    layer);

    list.add_element_description(std::move(desc));
}

} // namespace ivd::plate
