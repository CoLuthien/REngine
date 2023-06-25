
#pragma once

#include "plate/definitions.hpp"

#include "plate_render/drawable.hpp"
#include "plate_render/drawable_description.hpp"

#include <vector>

namespace ivd::plate
{

class PLATE_API drawable_batch
{
public:
    void add_drawables(drawable_description_list const&& list);

private:
    std::vector<drawable> drawables;
};

} // namespace ivd::plate