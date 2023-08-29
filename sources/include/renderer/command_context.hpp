
#pragma once

#include "renderer/definitions.hpp"

namespace ivd::render
{

class command_context_interface
{
public:
    virtual void begin_renderpass() = 0;
    virtual void begin_frame()      = 0;
    virtual void end_frame()        = 0;
    virtual void end_renderpass()   = 0;
};

} // namespace ivd::render
