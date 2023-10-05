
#pragma once

#include "rdi/buffer.hpp"
#include <vulkan/vulkan_raii.hpp>

namespace ivd::rdi
{
class vk_device;
class vk_buffer : public buffer
{
public:
    vk_buffer(std::weak_ptr<vk_device>           in_device,
              std::uint32_t                      in_size,
              std::uint32_t                      in_stride,
              std::span<vk::BufferUsageFlags>    usage,
              std::span<vk::MemoryPropertyFlags> in_properties,
              std::span<uint32_t>                in_shared_indices);

public:
    virtual std::span<std::byte> lock() override;

public:
    vk::raii::Buffer&       get_handle() { return m_buffer; }
    vk::raii::Buffer const& get_handle() const { return m_buffer; }

private:
    std::weak_ptr<vk_device> m_device;
    vk::raii::DeviceMemory   m_memory{nullptr};
    vk::raii::Buffer         m_buffer{nullptr};
};

} // namespace ivd::rdi