
#include "plate_element/box.hpp"
#include <cassert>

namespace ivd::plate
{

void
box::organize(layout_geometry const& geometry, std::vector<organized_plate>& plates)
{
}

void
box::draw(drawable_description_list& list, std::size_t layer_id, layout_geometry const& geometry)
{
}

void
box::content(std::initializer_list<plate_ptr> plates)
{
    assert(plates.size() == 1);
    get_composite()->initialize(plates);
}

} // namespace ivd::plate