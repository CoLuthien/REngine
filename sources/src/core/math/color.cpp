

#include "math/color.hpp"

namespace ivd::math
{

constexpr color color::white = color(255, 255, 255, 255);
constexpr color color::red   = color(255, 0, 0, 255);
constexpr color color::green = color(0, 255, 0, 255);
constexpr color color::blue  = color(0, 0, 255, 255);

} // namespace ivd::math