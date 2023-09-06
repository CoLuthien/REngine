
#pragma once

#include "engine_export.hpp"
#include "mesh/mesh_resources.hpp"

#include "math/point.hpp"
#include "math/vector.hpp"

#include "core_object.hpp"

#include <vector>

namespace ivd
{

struct ENGINE_API static_mesh_data : public hobject
{
    GENERATE_BODY()

public:
    std::vector<mesh_index> m_indices;

public:
    std::vector<point3d> m_vertices;
    std::vector<point3d> m_texcoords;

    std::vector<vector3d> m_normals;
    std::vector<vector3d> m_tangents;
    std::vector<vector3d> m_bitangents;
};

} // namespace ivd