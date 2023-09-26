
#include "vulkan_buffer.hpp"
#include "vulkan_device.hpp"

#include "meta/vulkan_helper.hpp"

#include <optional>
#include <numeric>
#include <functional>

#include <vulkan/vulkan_raii.hpp>

namespace ivd::rdi
{
namespace
{

std::optional<uint32_t>
findMemoryType(vk::raii::PhysicalDevice const& gpu,
               uint32_t                        filter,
               vk::MemoryPropertyFlagBits      properties)
{
    auto memProperties = gpu.getMemoryProperties();
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((filter & (1 << i)) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    return {};
}

} // namespace

vk_buffer::vk_buffer(std::weak_ptr<vk_device>           in_device,
                     std::uint32_t                      in_size,
                     std::uint32_t                      in_stride,
                     std::span<vk::BufferUsageFlags>    in_usage,
                     std::span<vk::MemoryPropertyFlags> in_properties,
                     std::span<uint32_t>                in_shared_indices)
    : buffer(in_size, in_stride), m_device(in_device)
{
    auto  device = m_device.lock();
    auto& handle = device->get_handle();

    auto buffer_usage = std::reduce(
        in_usage.begin(), in_usage.end(), *in_usage.begin(), std::bit_or<vk::BufferUsageFlags>{});

    auto mem_props = std::reduce(in_properties.begin(),
                                 in_properties.end(),
                                 *in_properties.begin(),
                                 std::bit_or<vk::MemoryPropertyFlags>{});

    // create buffer
    vk::BufferCreateInfo createInfo = {
        .size                  = size(),
        .usage                 = buffer_usage,
        .queueFamilyIndexCount = static_cast<uint32_t>(in_shared_indices.size()),
        .pQueueFamilyIndices   = in_shared_indices.data(),
    };

    m_buffer = handle.createBuffer(createInfo);

    // allocate gpu memory
    auto reqs = m_buffer.getMemoryRequirements();
    auto memory_type =
        findMemoryType(device->get_gpu_handle(),
                       reqs.memoryTypeBits,
                       static_cast<vk::MemoryPropertyFlagBits>((std::uint32_t)mem_props));

    if (memory_type.has_value())
    {
        vk::MemoryAllocateInfo allocInfo = {.allocationSize  = reqs.size,
                                            .memoryTypeIndex = memory_type.value()};

        m_memory = handle.allocateMemory(allocInfo);
        m_buffer.bindMemory(*m_memory, 0);
        valid = true;
    }
}
std::span<std::byte>
vk_buffer::lock()
{
    if (is_valid())
    {
    }

    return {};
}

} // namespace ivd::rdi