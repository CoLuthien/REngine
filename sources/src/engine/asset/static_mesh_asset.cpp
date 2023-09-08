

#include "asset/static_mesh_asset.hpp"

namespace ivd
{
namespace asset
{

static_mesh_asset::static_mesh_asset() : asset()
{
}
static_mesh_asset::~static_mesh_asset() = default;

std::vector<std::shared_ptr<static_mesh_description const>> const&
static_mesh_asset::get_meshes() const
{
    return m_descriptions;
}
// static_mesh_asset::static_mesh_asset() = default;
static_mesh_asset::static_mesh_asset(
    std::vector<std::shared_ptr<static_mesh_description const>>&& descriptions)
    : m_descriptions(std::move(descriptions))
{
}

std::shared_ptr<static_mesh_description const>
static_mesh_asset::get_mesh(std::size_t idx) const
{
    if (idx < m_descriptions.size())
    {
        return m_descriptions[idx];
    }
    return nullptr;
}

void
static_mesh_asset::allocate_mesh_description(std::vector<std::uint32_t>&& indices,
                                 std::vector<point3d>&&       vertices,
                                 std::vector<vector3d>&&      normals,
                                 std::vector<vector3d>&&      tangents,
                                 std::vector<vector3d>&&      bitangents,
                                 std::vector<vector3d>&&      texcoords)
{
    static_mesh_description desc{
        .m_indices    = std::move(indices),
        .m_vertices   = std::move(vertices),
        .m_normals    = std::move(normals),
        .m_texcoords  = std::move(texcoords),
        .m_tangents   = std::move(tangents),
        .m_bitangents = std::move(bitangents),
    };

    m_descriptions.emplace_back(std::make_shared<static_mesh_description>(desc));
}

} // namespace asset

} // namespace ivd