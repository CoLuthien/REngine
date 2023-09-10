
#pragma once

#include "render_export.hpp"

class RENDER_API render_resource
{
public:
    virtual void initialize_resource() {}
    virtual void release_resource() {}
};
