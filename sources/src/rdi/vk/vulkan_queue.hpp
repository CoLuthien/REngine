
#pragma once

#include "vulkan_command_buffer.hpp"

#include <vulkan/vulkan_raii.hpp>
#include <cstdint>

namespace ivd
{
namespace rdi
{
class vk_device;

class vk_queue
{
public:
    vk_queue(std::weak_ptr<vk_device> device, std::uint32_t in_family_indices);

public:
    void submit(vk::raii::CommandBuffer cmd_buffer);

public:
    inline std::uint32_t get_family_index() const { return m_family_index; }
    inline std::uint32_t get_queue_index() const { return m_queue_index; }

private:
    vk::raii::Queue m_queue{nullptr};
    std::uint32_t   m_family_index;
    std::uint32_t   m_queue_index;

    std::weak_ptr<vk_device> device;
};

} // namespace rdi

} // namespace ivd