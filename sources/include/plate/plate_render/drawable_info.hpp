
#pragma once

#include "plate/definitions.hpp"

namespace ivd::plate
{

// detailed information for element
struct drawable_info
{
public:
    virtual ~drawable_info() = default;
};

struct filled_box_drawable_info : public drawable_info
{
public:
};

} // namespace ivd::plate