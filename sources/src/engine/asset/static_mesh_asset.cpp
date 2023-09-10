

#include "asset/static_mesh_asset.hpp"

#include "import/static_mesh_importer.hpp"

namespace ivd
{
namespace asset
{

static_mesh_asset::static_mesh_asset(std::string const& filename, fs::path const& directory)
    : asset(filename, directory, easset_category::STATIC_MESH)
{
}
static_mesh_asset::~static_mesh_asset() = default;

void
static_mesh_asset::load()
{
    m_descriptions = importer::load_static_mesh(metadata.file_path);
}

std::vector<std::shared_ptr<static_mesh_description>> const&
static_mesh_asset::get_mesh_descriptions() const
{
    return m_descriptions;
}
// static_mesh_asset::static_mesh_asset() = default;
std::shared_ptr<static_mesh_description>
static_mesh_asset::get_mesh_description(std::size_t idx) const
{
    if (idx < m_descriptions.size())
    {
        return m_descriptions[idx];
    }
    return nullptr;
}

} // namespace asset

} // namespace ivd