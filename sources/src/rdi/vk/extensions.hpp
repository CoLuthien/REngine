
#pragma once

#include "rdi/common.hpp"

namespace ivd
{

namespace rdi
{

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

class vk_instance_extention : public vk_extension
{
public:
    vk_instance_extention(std::string_view name) : vk_extension(name) {}
    virtual ~vk_instance_extention() = default;
};

class vk_device_extension : public vk_extension
{
public:
    vk_device_extension(std::string_view name) : vk_extension(name) {}
    virtual ~vk_device_extension() = default;
};

} // namespace rdi

} // namespace ivd
