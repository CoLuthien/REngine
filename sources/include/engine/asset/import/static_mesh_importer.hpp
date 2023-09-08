
#pragma once

#include "engine_export.hpp"
#include "asset/import/asset_importer.hpp"

#include <queue>

namespace ivd
{
namespace asset
{

class ENGINE_API static_mesh_importer : public asset_importer
{
public:
    static_mesh_importer()          = default;
    virtual ~static_mesh_importer() = default;

public:
    virtual std::future<asset*> async_load_asset(std::unique_ptr<import_task> task) override;
    virtual asset*              load_asset(std::unique_ptr<import_task> task) override;
};

} // namespace asset

} // namespace ivd