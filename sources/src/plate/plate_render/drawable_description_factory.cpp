
#include "plate_render/drawable_description_factory.hpp"
#include "plate_render/drawable_info.hpp"
#include "plate_core/layout/margin.hpp"

#include <memory>

namespace ivd::plate
{

void
drawable_description_factory::make_box_description(drawable_description_list& list,
                                                   std::size_t                layer,
                                                   layout_geometry            geometry,
                                                   color                      in_color,
                                                   margin                     in_margin)
{
    drawable_description desc;

    auto info = std::make_unique<filled_box_drawable_info>();

    info->m_margin = in_margin;

    desc.initialize(
        drawable_type_e::BOX, std::move(info), geometry.get_location(), geometry.get_size(), layer);

    list.add_element_description(std::move(desc));
}

} // namespace ivd::plate
