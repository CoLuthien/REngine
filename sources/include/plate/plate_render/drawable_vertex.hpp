
#pragma once

#include "plate_export.hpp"

#include "math/point.hpp"
#include "math/color.hpp"

#include <cstdint>

namespace ivd::plate
{

using drawable_index = std::uint32_t;

struct PLATE_API drawable_vertex
{
    point2f position;
    point2f texture_coordinate;
    color    vertex_color;
};

} // namespace ivd::plate