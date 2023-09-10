
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
    using data_type = std::shared_ptr<static_mesh_description>;

public:
    static_mesh_asset() = default;
    static_mesh_asset(std::string const& filename, fs::path const& directory);
    virtual ~static_mesh_asset();

public:
    virtual void load() override;

public:
    std::size_t                   get_num_meshes() { return m_descriptions.size(); }
    std::vector<data_type> const& get_mesh_descriptions() const;
    data_type                     get_mesh_description(std::size_t idx) const;



private:
    REFLECT_FIELD(std::vector<data_type>, m_descriptions);
};

} // namespace asset

} // namespace ivd