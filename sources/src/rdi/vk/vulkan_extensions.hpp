
#pragma once

#include "vk/vulkan_commons.hpp"

namespace ivd
{

namespace rdi
{
using device_extensions = std::vector<class vk_device_extension>;

class vk_extension
{
public:
    vk_extension(std::string_view name) : m_name(name) {}
    virtual ~vk_extension() = default;

public:
    inline char const* get_name() const { return m_name.c_str(); }

protected:
    std::string m_name;
};

class vk_device_extension : public vk_extension
{
public:
    vk_device_extension(std::string_view name) : vk_extension(name) {}
    virtual ~vk_device_extension() = default;

public:
    static device_extensions get_required();

public:
    bool check_available(std::vector<vk::ExtensionProperties> const& props) const;

private:
};

} // namespace rdi

} // namespace ivd
