
#pragma once

namespace ivd
{
namespace rdi
{

class vulkan_swapchain
{
public:
    vulkan_swapchain(VkInstance                    InInstance,
                     vk&                           InDevice,
                     void*                         WindowHandle,
                     EPixelFormat&                 InOutPixelFormat,
                     uint32                        Width,
                     uint32                        Height,
                     bool                          bIsFullscreen,
                     uint32*                       InOutDesiredNumBackBuffers,
                     TArray<VkImage>&              OutImages,
                     int8                          bLockToVsync,
                     FVulkanSwapChainRecreateInfo* RecreateInfo);
};
} // namespace rdi

} // namespace ivd