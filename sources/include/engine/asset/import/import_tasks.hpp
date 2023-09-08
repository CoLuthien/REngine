
#pragma once

#include "engine_export.hpp"
#include "asset/asset.hpp"

#include <filesystem>

namespace fs = std::filesystem;

namespace ivd
{
namespace asset
{

struct ENGINE_API import_task
{
public:
    fs::path        file_path = "";
    easset_category kind      = easset_category::INVALID;
};

} // namespace asset

} // namespace ivd