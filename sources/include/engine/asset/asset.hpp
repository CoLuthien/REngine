
#pragma once
#include "engine_export.hpp"

#include "core.hpp"
#include "core_object.hpp"

#include <filesystem>
#include <future>

namespace fs = std::filesystem;

namespace ivd
{
namespace asset
{
enum class easset_category
{
    STATIC_MESH   = 0,
    SKELETAL_MESH = 1,
    MATERIAL      = 2,
    TEXTURE       = 3,
    FONT          = 4,
    SHADER        = 5,
    SOUND         = 6,
    TEXT          = 7,
    INVALID,
};

struct ENGINE_API asset_metadata
{
    GENERATE_STRUCT()
public:
    REFLECT_FIELD(std::string, filename, "invalid");
    REFLECT_FIELD(std::size_t, file_size, 0);
    REFLECT_FIELD(fs::path, file_directory, fs::current_path());
    REFLECT_FIELD(fs::path, file_path);
    REFLECT_FIELD(easset_category, asset_type, easset_category::INVALID);
};

class ENGINE_API asset : public hobject
{
    GENERATE_BODY();

public:
    asset() = default;
    asset(std::string const& filename, fs::path const& directory, easset_category type);

public:
    enum class status
    {
        IMPORT_FAILED = 0,
        UNIMPORTED,
        IMPORTING,
        IMPORTED,
        INVALID
    };

public:
    std::future<void> async_load();
    virtual void      load() = 0;

public:
    asset_metadata get_metadata();

public:
    REFLECT_FIELD(asset_metadata, metadata);
    REFLECT_FIELD(status, state);
};

} // namespace asset

} // namespace ivd