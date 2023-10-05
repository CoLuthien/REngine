
#include "render_device.hpp"

namespace ivd::rdi
{

vk_render_device::vk_render_device(std::string_view title) : render_device(title)
{
    vk::ApplicationInfo appInfo = {.pNext              = nullptr,
                                   .pApplicationName   = m_title.c_str(),
                                   .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
                                   .pEngineName        = "Invader",
                                   .engineVersion      = VK_MAKE_VERSION(0, 0, 1),
                                   .apiVersion         = VK_API_VERSION_1_3};
}

} // namespace ivd::rdi