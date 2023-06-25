
#include "plate_render/drawable_description.hpp"
#include "plate_render/drawable_info.hpp"
#include "drawable_factory.hpp"

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

drawable
drawable_description::make_drawable() const
{

    switch (type)
    {
    case drawable_type_e::BOX: {
        return drawable_factory::make_filled_box(*this);
    }
    case drawable_type_e::LINE: {
        break;
    }
    }
    return {};
}

void
drawable_description_list::add_element_description(drawable_description&& desc)
{
    descriptions.emplace_back(std::move(desc));
}

} // namespace ivd::plate