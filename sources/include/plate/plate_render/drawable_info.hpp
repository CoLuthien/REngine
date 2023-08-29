
#pragma once

#include "plate_core/layout/margin.hpp"

namespace ivd::plate
{

// detailed information for element
struct drawable_info
{
public:
    drawable_info()          = default;
    virtual ~drawable_info() = default;
};

struct filled_box_drawable_info : public drawable_info
{
public:
    virtual ~filled_box_drawable_info() = default;

public:
    margin m_margin;
};

} // namespace ivd::plate