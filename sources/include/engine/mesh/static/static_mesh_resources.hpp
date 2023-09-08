
#pragma once

#include "engine_export.hpp"
#include "mesh/mesh_resources.hpp"

#include "math/point.hpp"
#include "math/vector.hpp"

#include "core.hpp"
#include "core_object.hpp"

#include <vector>

namespace ivd
{

struct ENGINE_API static_mesh_description
{
    GENERATE_STRUCT()

public:
    REFLECT_FIELD(std::vector<std::uint32_t>, m_indices);
    REFLECT_FIELD(std::vector<point3d>, m_vertices);

public:
    REFLECT_FIELD(std::vector<vector3d>, m_normals);
    REFLECT_FIELD(std::vector<vector3d>, m_texcoords);
    REFLECT_FIELD(std::vector<vector3d>, m_tangents);
    REFLECT_FIELD(std::vector<vector3d>, m_bitangents);
};

} // namespace ivd