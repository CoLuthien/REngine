
#pragma once

#include <string_view>
#include <vector>

#include "rdi/rdi_commons.hpp"
#include <vulkan/vulkan_raii.hpp>

namespace ivd::rdi
{
#if USE_VALIDATION_LAYER
static constexpr bool VALIDATION_LAYER_ENABLED = true;
#else
static constexpr bool enable_validation_layer = false;
#endif
static std::vector<char const*> const DEFAULT_VALIDATION_LAYERS = {"VK_LAYER_KHRONOS_validation"};

static std::vector<char const*> const DEFAULT_INSTANCE_EXTENSION = {
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME,
    VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME,
    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
};

static std::vector<char const*> const INSTANCE_DEBUG_EXTENSION = {
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
    VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
};

static constexpr auto RENGINE_VERSION        = VK_MAKE_VERSION(0, 0, 0);
static constexpr auto RENGINE_VK_API_VERSION = VK_API_VERSION_1_3;

} // namespace ivd::rdi