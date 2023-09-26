
#include "vulkan_extensions.hpp"

namespace ivd::rdi
{

device_extensions
vk_device_extension::get_required()
{
    device_extensions extensions{};

    extensions.emplace_back(vk_device_extension(VK_KHR_SWAPCHAIN_EXTENSION_NAME));

    return extensions;
}

bool
vk_device_extension::check_available(std::vector<vk::ExtensionProperties> const& props) const
{
    return std::any_of(
        props.begin(), props.end(), [&name = m_name](vk::ExtensionProperties const& prop) {
            return name == prop.extensionName.data();
        });
}

} // namespace ivd::rdi