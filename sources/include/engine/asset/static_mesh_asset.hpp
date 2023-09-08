
#pragma once

#include "engine_export.hpp"
#include "asset/asset.hpp"
#include "mesh/static/static_mesh_resources.hpp"

#include "core.hpp"
#include "core_object.hpp"

#include <vector>

namespace ivd
{

namespace asset
{

class ENGINE_API static_mesh_asset : public asset
{
    GENERATE_BODY()

public:
    using data_type = std::shared_ptr<static_mesh_description const>;

public:
    static_mesh_asset();
    virtual ~static_mesh_asset();

    static_mesh_asset(std::vector<data_type>&& descriptions);

public:
    std::vector<data_type> const& get_meshes() const;
    data_type                     get_mesh(std::size_t idx) const;

public:
    void allocate_mesh_description(std::vector<std::uint32_t>&& indices,
                                   std::vector<point3d>&&       vertices,
                                   std::vector<vector3d>&&      normals,
                                   std::vector<vector3d>&&      tangents,
                                   std::vector<vector3d>&&      bitangents,
                                   std::vector<vector3d>&&      texcoords);

private:
    REFLECT_FIELD(std::vector<data_type>, m_descriptions);
};

} // namespace asset

} // namespace ivd