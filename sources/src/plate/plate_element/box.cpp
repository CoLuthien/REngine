
#include "plate_element/box.hpp"
#include <cassert>

namespace ivd::plate
{

void
box::content(std::initializer_list<plate_ptr> plates)
{
    assert(plates.size() == 1);
    get_composite()->initialize(plates);
}

} // namespace ivd::plate