
#pragma once

#include "plate/definitions.hpp"

namespace ivd::plate
{

// detailed information for element
class drawable_info
{
public:
    virtual ~drawable_info() = default;
};

class filled_box_drawable_info : public drawable_info
{
};

} // namespace ivd::plate