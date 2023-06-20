
#pragma once

#include "plate/definitions.hpp"
#include "plate_types.hpp"

#include "plate_core/reply.hpp"

#include <memory>

namespace ivd::plate
{
class slot_base;

PLATE_API void initialize();

class PLATE_API plate : std::enable_shared_from_this<plate>
{
public:
    virtual reply click(/*todo*/) { return {}; }
    virtual reply key(/*todo*/) { return {}; }

    virtual void draw(/*todo*/) {}

public:
    virtual slot_base* get_composite() = 0;

private:
};

} // namespace ivd::plate