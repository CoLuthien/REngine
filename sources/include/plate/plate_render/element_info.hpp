
#pragma once

#include "plate/definitions.hpp"

namespace ivd::plate
{

class element_info
{
public:
    virtual ~element_info() = default;
};

class box_element_info : public element_info
{
};

} // namespace ivd::plate