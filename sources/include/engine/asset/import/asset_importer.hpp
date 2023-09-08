
#pragma once

#include "engine_export.hpp"
#include "asset/import/import_tasks.hpp"
#include "asset/asset.hpp"

#include <future>
#include <memory>

namespace ivd
{
namespace asset
{

class ENGINE_API asset_importer
{
public:
    asset_importer() = default;

public:
    virtual std::future<asset*> async_load_asset(std::unique_ptr<import_task> task) = 0;
    virtual asset*              load_asset(std::unique_ptr<import_task> task)       = 0;
};

} // namespace asset

} // namespace ivd
