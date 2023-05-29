
#include "application.hpp"

SwapChainSupportDetails
TriangleApplication::querySwapChainSupport(vk::raii::PhysicalDevice const& device)
{
    SwapChainSupportDetails details;
    details.capabilities = device.getSurfaceCapabilitiesKHR(*surface);
    details.formats      = device.getSurfaceFormatsKHR(*surface);
    details.presentModes = device.getSurfacePresentModesKHR(*surface);

    return details;
}

static void
framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto app = reinterpret_cast<TriangleApplication*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

void
TriangleApplication::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

std::vector<const char*>
TriangleApplication::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions,
                                        glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

vk::SurfaceFormatKHR
TriangleApplication::chooseSwapSurfaceFormat(
    std::vector<vk::SurfaceFormatKHR> const& formats)
{
    for (auto const& format : formats)
    {
        if (format.format == vk::Format::eB8G8R8A8Srgb &&
            format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
        {
            return format;
        }
    }

    return formats[0];
}
bool
TriangleApplication::checkDeviceExtensionSupport(vk::raii::PhysicalDevice const& device)
{
    auto extensions = device.enumerateDeviceExtensionProperties();
    std::set<std::string> requiredExtensions(deviceExtensions.begin(),
                                             deviceExtensions.end());

    for (auto const& extension : extensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

bool
TriangleApplication::isDeviceSuitable(vk::raii::PhysicalDevice const& device)
{
    auto properties = device.getProperties();
    auto features   = device.getFeatures();

    bool extensionSupported = checkDeviceExtensionSupport(device);

    bool isSwapChainAdquate = false;

    if (extensionSupported)
    {
        auto detail = querySwapChainSupport(device);

        isSwapChainAdquate = !detail.formats.empty() && !detail.presentModes.empty();
    }

    auto indices = findQueueFamilies(device);
    return (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) &&
           features.geometryShader && indices.isComplete() && extensionSupported &&
           isSwapChainAdquate;
}

vk::PresentModeKHR
TriangleApplication::chooseSwapPresentMode(std::vector<vk::PresentModeKHR> const& modes)
{
    for (auto const& mode : modes)
    {
        if (mode == vk::PresentModeKHR::eMailbox)
        {
            return mode;
        }
    }
    return vk::PresentModeKHR::eFifo;
}

vk::Extent2D
TriangleApplication::chooseSwapExtent(vk::SurfaceCapabilitiesKHR const& capabilities)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    }
    else
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        vk::Extent2D actualExtent{.width  = static_cast<uint32_t>(width),
                                  .height = static_cast<uint32_t>(height)};

        actualExtent.width  = std::clamp(actualExtent.width,
                                        capabilities.minImageExtent.width,
                                        capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height,
                                         capabilities.minImageExtent.height,
                                         capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

vk::raii::ShaderModule
TriangleApplication::createShaderModule(std::vector<std::byte> const& bytecode)
{
    vk::ShaderModuleCreateInfo createInfo{
        .codeSize = bytecode.size(),
        .pCode    = reinterpret_cast<uint32_t const*>(bytecode.data()),
    };

    return device.createShaderModule(createInfo);
}

QueueFamilyIndices
TriangleApplication::findQueueFamilies(vk::raii::PhysicalDevice const& device)
{
    QueueFamilyIndices indices;

    auto properties = device.getQueueFamilyProperties();
    int i           = 0;
    for (auto const& family : properties)
    {
        if (family.queueFlags & vk::QueueFlagBits::eGraphics)
        {
            indices.graphicsFamily = i;
        }
        if (device.getSurfaceSupportKHR(i, *surface))
        {
            indices.presentFamily = i;
        }
        if (indices.isComplete())
        {
            break;
        }
        i++;
    }

    return indices;
}

bool
TriangleApplication::checkValidationLayerSupport()
{
    std::vector<vk::LayerProperties> availableLayers =
        vk::enumerateInstanceLayerProperties();

    for (const char* layerName : validationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers)
        {
            if (layerName == (std::string_view)layerProperties.layerName)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    return true;
}

void
TriangleApplication::recordCommandBuffer(vk::raii::CommandBuffer& buffer,
                                         uint32_t imageIndex)
{
    vk::CommandBufferBeginInfo beginInfo{
        .pNext            = nullptr,
        .flags            = {},
        .pInheritanceInfo = nullptr,
    };

    buffer.begin(beginInfo);

    vk::ClearValue clearColor;
    clearColor.setColor({0.f, 0.f, 0.f, 1.f});
    vk::RenderPassBeginInfo renderPassInfo{
        .renderPass  = *renderPass,
        .framebuffer = *swapchainFramebuffers[imageIndex],
        .renderArea =
            {
                .offset = {0, 0},
                .extent = imageExtent,
            },
        .clearValueCount = 1,
        .pClearValues    = &clearColor,
    };

    buffer.beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);

    buffer.bindPipeline(vk::PipelineBindPoint::eGraphics, *graphicsPipeline);
    buffer.bindVertexBuffers(0, *vertexBuffer, {0});

    buffer.setViewport(0, viewport);

    buffer.setScissor(0, scissor);

    buffer.draw(3, 1, 0, 0);

    buffer.endRenderPass();

    buffer.end();
}

void
TriangleApplication::recreateSwapChain()
{
    device.waitIdle();

    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    cleanupSwapChain();
    createSwapChain();
    createImageViews();
    createFramebuffers();
}
void
TriangleApplication::cleanupSwapChain()
{
    swapchainFramebuffers.clear();
    swapImageViews.clear();
    swapChain.clear();
}

void
TriangleApplication::drawFrame()
{
    auto& inFlight       = inFlights[currentFrameIdx];
    auto& imageAvailable = imageAvailables[currentFrameIdx];
    auto& commandBuffer  = commandBuffers[currentFrameIdx];
    auto& renderFinished = renderFinishes[currentFrameIdx];

    auto waitResult =
        device.waitForFences({*inFlight}, true, std::numeric_limits<uint64_t>::max());
    if (waitResult != vk::Result::eSuccess)
    {
        throw std::runtime_error{"Failed to wait in flight fence"};
    }

    commandBuffer.reset();
    auto [acquireResult, imageIndex] =
        swapChain.acquireNextImage(std::numeric_limits<uint64_t>::max(), *imageAvailable);

    if (acquireResult == vk::Result::eErrorOutOfDateKHR)
    {
        recreateSwapChain();
        return;
    }
    else if (acquireResult != vk::Result::eSuccess &&
             acquireResult != vk::Result::eSuboptimalKHR)
    {
        throw std::runtime_error("failed to acquire swap chain image!");
    }
    device.resetFences({*inFlight});
    recordCommandBuffer(commandBuffer, imageIndex);

    vk::PipelineStageFlags waitStages[] = {
        vk::PipelineStageFlagBits::eColorAttachmentOutput};

    vk::SubmitInfo submitInfo{.waitSemaphoreCount   = 1,
                              .pWaitSemaphores      = &(*imageAvailable),
                              .pWaitDstStageMask    = waitStages,
                              .commandBufferCount   = 1,
                              .pCommandBuffers      = &(*commandBuffer),
                              .signalSemaphoreCount = 1,
                              .pSignalSemaphores    = &(*renderFinished)};

    graphicsQueue.submit({submitInfo}, *inFlight);

    vk::PresentInfoKHR presentInfo{
        .pNext              = nullptr,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores    = &(*renderFinished),
        .swapchainCount     = 1,
        .pSwapchains        = &(*swapChain),
        .pImageIndices      = &imageIndex,
    };

    try
    {
        auto result = presentQueue.presentKHR(presentInfo);
    }
    catch (vk::OutOfDateKHRError& err)
    {
        recreateSwapChain();
    }

    currentFrameIdx = (currentFrameIdx + 1) % ConcurrentFrames;
}
