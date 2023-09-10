
#pragma once

#include "rdi_export.hpp"

namespace ivd
{
namespace rdi
{

class RDI_API i_render_device
{
public:
    virtual ~i_render_device() {}

    virtual void initialize() = 0;
    virtual void shutdown()   = 0;
};
} // namespace rdi

} // namespace ivd