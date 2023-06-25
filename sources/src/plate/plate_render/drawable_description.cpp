
#include "plate_render/drawable_description.hpp"
#include "plate_render/drawable_info.hpp"

namespace ivd::plate
{

drawable_description::drawable_description()                                           = default;
drawable_description::~drawable_description()                                          = default;
drawable_description::drawable_description(drawable_description&&)                     = default;
drawable_description& drawable_description::operator=(drawable_description&&) noexcept = default;

void
drawable_description::initialize(drawable_type_e                in_type,
                                 std::unique_ptr<drawable_info> in_info,
                                 point2_f                       in_location,
                                 extent2_f                      in_size,
                                 layer_id_t                     in_layer)
{
    type     = in_type;
    info     = std::move(in_info);
    size     = in_size;
    location = in_location;
    layer_id = in_layer;
}

void
drawable_description_list::add_element_description(drawable_description&& desc)
{
    drawables.emplace_back(std::move(desc));
}

} // namespace ivd::plate