
#pragma once

#include "plate/definitions.hpp"

#include <glm/glm.hpp>
namespace glfw
{
class Window;
}

using plate_host = glfw::Window;

namespace ivd::plate
{
using point = glm::ivec2;

constexpr auto full_extent = std::numeric_limits<int>::max();

struct view_limits
{
    point min = {0.0, 0.0};
    point max = {full_extent, full_extent};
};

struct rect
{
private:
    int left, right, top, bottom;
};

} // namespace ivd::plate