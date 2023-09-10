
#pragma once

#include "engine_export.hpp"
#include "mesh/static/static_mesh_resources.hpp"

#include <vector>
#include <memory>
#include <filesystem>

#include <queue>

namespace fs = std::filesystem;

namespace ivd
{
namespace asset
{

namespace importer
{
std::vector<std::shared_ptr<static_mesh_description>> load_static_mesh(fs::path const& filename);

} // namespace importer

} // namespace asset

} // namespace ivd