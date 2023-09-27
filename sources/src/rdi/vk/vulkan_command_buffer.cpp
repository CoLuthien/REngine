
#include "vulkan_command_buffer.hpp"
#include "vulkan_device.hpp"
#include <cstdint>
namespace ivd::rdi
{

vk_cmd_buffer::vk_cmd_buffer(std::weak_ptr<vk_device> device, bool is_upload_only)
{
}

void
vk_cmd_buffer::start_record()
{
    auto device = m_device.lock();
    if (nullptr == device)
    {
        return;
    }

    auto& handle = device->get_handle();

    auto&& wait_result =
        handle.waitForFences({*wait_previous}, true, std::numeric_limits<std::uint32_t>::max());

    if (wait_result != vk::Result::eSuccess)
    {
        // todo log
        return;
    }
    m_buffer.reset();
    handle.resetFences({*wait_previous});
}

void
vk_cmd_buffer::stop_record()
{
}

} // namespace ivd::rdi