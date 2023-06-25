
#pragma once

#include "plate/definitions.hpp"

#include "math/point.hpp"
#include "math/color.hpp"

#include <cstdint>

namespace ivd::plate
{

using drawable_index = std::uint32_t;

struct PLATE_API drawable_vertex
{
    point2_f position;
    point2_f texture_coordinate;
    color    vertex_color;
};

} // namespace ivd::plate