
#pragma once

#include "vk/rdi_vulkan.hpp"

#include <vulkan/vulkan_raii.hpp>

#include <memory>

namespace ivd
{

namespace rdi
{

class vk_device;

class vk_cmd_buffer
{
public:
    vk_cmd_buffer(std::weak_ptr<vk_device> device, bool is_upload_only);

public:
    void start_record();
    void stop_record();

public:
    inline vk::raii::CommandBuffer& get_handle() { return m_buffer; }

private:
    std::weak_ptr<vk_device> m_device;
    vk::raii::CommandBuffer  m_buffer{nullptr};

private:
    vk::raii::Fence     wait_previous{nullptr};
    vk::raii::Semaphore wait_image{nullptr};
    vk::raii::Semaphore wait_render{nullptr};
};

} // namespace rdi

} // namespace ivd