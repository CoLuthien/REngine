
#pragma once

#include "utils/non_copyable.hpp"

#include <vulkan/vulkan_raii.hpp>

namespace ivd
{
namespace rdi
{

class vk_device : non_copyable
{
public:
    vk_device(vk::PhysicalDevice GPU);

public:
    vk::raii::Device&         get_handle() { return m_device; }
    vk::raii::PhysicalDevice& get_gpu_handle() { return m_gpu; }

private:
    vk::raii::Device         m_device{nullptr};
    vk::raii::PhysicalDevice m_gpu{nullptr};
    vk::raii::CommandPool    m_transfer_commands{nullptr};
};

} // namespace rdi

} // namespace ivd