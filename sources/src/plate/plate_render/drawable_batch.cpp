
#include "plate_render/drawable_batch.hpp"

namespace ivd::plate
{

void
drawable_batch::add_drawables(drawable_description_list const&& list)
{
    for (auto const& desc : list.descriptions)
    {
        drawables.emplace_back(desc.make_drawable());
    }
}

} // namespace ivd::plate