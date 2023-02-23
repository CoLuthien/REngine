
#pragma once

#include "concepts.hpp"
#include "meta/type_list.hpp"

#include "HAL/platforms.hpp"
#include <cstddef>

namespace ivd
{

class DLLEXPORT hobject_t
{
public:
    using super = std::nullptr_t;
    using this_type = hobject_t;

    using pedigree_list = meta::typelist<super>;
    hobject_t();

public:
    // delete copy;
    hobject_t& operator=(hobject_t const&) = delete;
    hobject_t(hobject_t const&)            = delete;
    // delete move
    hobject_t& operator=(hobject_t&&) = delete;
    hobject_t(hobject_t&&)            = delete;

private:
    std::size_t obj_idx;
};

} // namespace ivd
