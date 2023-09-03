
#pragma once

#include "plate_export.hpp"

#include "plate_render/drawable.hpp"
#include "plate_render/drawable_description.hpp"

namespace ivd::plate
{

class drawable_factory
{
public:
    static drawable make_filled_box(drawable_description const& desc);
};

} // namespace ivd::plate