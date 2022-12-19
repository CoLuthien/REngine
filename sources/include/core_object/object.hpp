
#pragma once

#include "concepts.hpp"
#include <cstddef>

namespace hln
{

class hobject_t
{
public:
    using this_type = hobject_t;
    hobject_t()     = default;
    // need a antigen for GC

public:
    // delte copy;
    hobject_t& operator=(hobject_t const&) = delete;
    hobject_t(hobject_t const&)            = delete;
    // delete move
    hobject_t& operator=(hobject_t&&) = delete;
    hobject_t(hobject_t&&)            = delete;

private:
    std::size_t obj_idx;
};

} // namespace hln
