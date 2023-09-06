
#pragma once

#include "engine_export.hpp"

#include <cstdint>

namespace ivd
{

struct ENGINE_API mesh_index
{
public:
    mesh_index() = default;

public:
    std::int32_t vertex_idx    = -1;
    std::int32_t normal_idx    = -1;
    std::int32_t texcoord_idx  = -1;
    std::int32_t tangent_idx   = -1;
    std::int32_t bitangent_idx = -1;
};

} // namespace ivd