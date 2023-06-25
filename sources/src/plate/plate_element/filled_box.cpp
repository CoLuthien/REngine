

#include "plate_element/filled_box.hpp"

namespace ivd::plate
{

filled_box::filled_box()  = default;
filled_box::~filled_box() = default;

void
filled_box::draw(element_list& list, std::size_t layer_id, layout_geometry const& geometry)
{
}

} // namespace ivd::plate