

#include "asset/asset.hpp"

namespace ivd
{
namespace asset
{

asset::asset(std::string const& filename, fs::path const& directory, easset_category type)
{
    metadata = {.filename       = filename,
                .file_directory = directory,
                .file_path      = directory.generic_string() + filename,
                .asset_type     = type};
}

std::future<void>
asset::async_load()
{
    return std::async(std::launch::async, &this_type::load, this);
}

asset_metadata
asset::get_metadata() const
{
    return metadata;
}
} // namespace asset
} // namespace ivd