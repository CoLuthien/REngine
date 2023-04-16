
#include "application.hpp"

static VKAPI_ATTR vk::Bool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData,
              void* pUserData)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}
static std::vector<std::byte>
readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        exit(-1);
    }
    std::size_t fileSize = file.tellg();
    std::vector<std::byte> buffer(fileSize);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    file.close();

    return buffer;
}
SwapChainSupportDetails
HelloTriangleApplication::querySwapChainSupport(vk::raii::PhysicalDevice const& device)
{
    SwapChainSupportDetails details;
    details.capabilities = device.getSurfaceCapabilitiesKHR(**surface);
    details.formats      = device.getSurfaceFormatsKHR(**surface);
    details.presentModes = device.getSurfacePresentModesKHR(**surface);

    return details;
}
void
HelloTriangleApplication::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

std::vector<const char*>
HelloTriangleApplication::getRequiredExtensions()
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

void
HelloTriangleApplication::createSurface()
{
    VkSurfaceKHR _surface;
    if (glfwCreateWindowSurface(
            static_cast<VkInstance>(**instance), window, nullptr, &_surface))
    {
        std::cerr << "Failed to create window surface :(\n";
        exit(-1);
    }

    surface = std::make_unique<vk::raii::SurfaceKHR>(*instance, _surface);
}
void
HelloTriangleApplication::createInstance()
{

    if (enableValidationLayers && !checkValidationLayerSupport())
    {
        std::cout << "validation layers requested, but not available!\n";
        exit(-1);
    }
    vk::raii::Context context;

    vk::ApplicationInfo appInfo{.pApplicationName   = "Hello Triangle",
                                .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                                .pEngineName        = "No Engine",
                                .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
                                .apiVersion         = VK_API_VERSION_1_0};

    auto extensions = getRequiredExtensions();
    vk::InstanceCreateInfo createInfo;
    if (enableValidationLayers)
    {
        vk::DebugUtilsMessengerCreateInfoEXT createDebugInfo{
            .messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
                               vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                               vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose,
            .messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                           vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                           vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
            .pfnUserCallback = &debugCallback,
            .pUserData       = nullptr};

        createInfo = {.pNext             = &createDebugInfo,
                      .pApplicationInfo  = &appInfo,
                      .enabledLayerCount = static_cast<uint32_t>(validationLayers.size()),
                      .ppEnabledLayerNames     = validationLayers.data(),
                      .enabledExtensionCount   = static_cast<uint32_t>(extensions.size()),
                      .ppEnabledExtensionNames = extensions.data()};
    }
    else
    {
        createInfo = {.pApplicationInfo        = &appInfo,
                      .enabledExtensionCount   = static_cast<uint32_t>(extensions.size()),
                      .ppEnabledExtensionNames = extensions.data()};
    }

    instance = std::make_unique<vk::raii::Instance>(context, createInfo);
}

vk::SurfaceFormatKHR
HelloTriangleApplication::chooseSwapSurfaceFormat(
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
HelloTriangleApplication::checkDeviceExtensionSupport(
    vk::raii::PhysicalDevice const& device)
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
HelloTriangleApplication::isDeviceSuitable(vk::raii::PhysicalDevice const& device)
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
HelloTriangleApplication::chooseSwapPresentMode(
    std::vector<vk::PresentModeKHR> const& modes)
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
HelloTriangleApplication::chooseSwapExtent(vk::SurfaceCapabilitiesKHR const& capabilities)
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

void
HelloTriangleApplication::createSwapChain()
{
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(*physicalDevice);

    vk::SurfaceFormatKHR surfaceFormat =
        chooseSwapSurfaceFormat(swapChainSupport.formats);
    vk::PresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    vk::Extent2D extent            = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 &&
        imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }
    QueueFamilyIndices indices    = findQueueFamilies(*physicalDevice);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(),
                                     indices.presentFamily.value()};
    vk::SwapchainCreateInfoKHR createInfo;

    if (indices.graphicsFamily != indices.presentFamily)
    {
        createInfo = {.surface               = **surface,
                      .minImageCount         = imageCount,
                      .imageFormat           = surfaceFormat.format,
                      .imageColorSpace       = surfaceFormat.colorSpace,
                      .imageExtent           = extent,
                      .imageArrayLayers      = 1,
                      .imageUsage            = vk::ImageUsageFlagBits::eColorAttachment,
                      .imageSharingMode      = vk::SharingMode::eConcurrent,
                      .queueFamilyIndexCount = 2,
                      .pQueueFamilyIndices   = queueFamilyIndices};
    }
    else
    {
        createInfo = {.surface               = **surface,
                      .minImageCount         = imageCount,
                      .imageFormat           = surfaceFormat.format,
                      .imageColorSpace       = surfaceFormat.colorSpace,
                      .imageExtent           = extent,
                      .imageArrayLayers      = 1,
                      .imageUsage            = vk::ImageUsageFlagBits::eColorAttachment,
                      .imageSharingMode      = vk::SharingMode::eExclusive,
                      .queueFamilyIndexCount = 0,
                      .pQueueFamilyIndices   = nullptr};
    }
    createInfo.setPreTransform(swapChainSupport.capabilities.currentTransform);
    createInfo.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
    createInfo.setPresentMode(presentMode);
    createInfo.setClipped(VK_TRUE);
    createInfo.setOldSwapchain(nullptr);

    swapChain =
        std::make_unique<vk::raii::SwapchainKHR>(device->createSwapchainKHR(createInfo));
    assert(swapChain != nullptr);

    auto images = swapChain->getImages();

    swapImages  = images;
    imageFormat = surfaceFormat.format;
    imageExtent = extent;
}

void
HelloTriangleApplication::createImageViews()
{
    for (size_t i = 0; i < swapImages.size(); i++)
    {
        vk::ImageViewCreateInfo createInfo{
            .image            = swapImages[i],
            .viewType         = vk::ImageViewType::e2D,
            .format           = imageFormat,
            .components       = {.r = vk::ComponentSwizzle::eIdentity,
                                 .g = vk::ComponentSwizzle::eIdentity,
                                 .b = vk::ComponentSwizzle::eIdentity,
                                 .a = vk::ComponentSwizzle::eIdentity},
            .subresourceRange = {.aspectMask     = vk::ImageAspectFlagBits::eColor,
                                 .baseMipLevel   = 0,
                                 .levelCount     = 1,
                                 .baseArrayLayer = 0,
                                 .layerCount     = 1},
        };

        swapImageViews.emplace_back(device->createImageView(createInfo));
    }
}

vk::raii::ShaderModule
HelloTriangleApplication::createShaderModule(std::vector<std::byte> const& bytecode)
{
    vk::ShaderModuleCreateInfo createInfo{
        .codeSize = bytecode.size(),
        .pCode    = reinterpret_cast<uint32_t const*>(bytecode.data()),
    };

    return std::move(device->createShaderModule(createInfo));
}
void
HelloTriangleApplication::createGraphicsPipeline()
{
    auto vertshader = readFile("shaders/example/shader.vert.spv");
    auto fragshader = readFile("shaders/example/shader.frag.spv");

    auto vertModule = createShaderModule(vertshader);
    auto fragModule = createShaderModule(fragshader);

    vk::PipelineShaderStageCreateInfo createVertShaderInfo{
        .stage               = vk::ShaderStageFlagBits::eVertex,
        .module              = *vertModule,
        .pName               = "main",
        .pSpecializationInfo = nullptr,
    };
    vk::PipelineShaderStageCreateInfo createFragShaderInfo{
        .stage               = vk::ShaderStageFlagBits::eFragment,
        .module              = *fragModule,
        .pName               = "main",
        .pSpecializationInfo = nullptr,
    };
    vk::PipelineShaderStageCreateInfo shaderStages[] = {
        createVertShaderInfo,
        createFragShaderInfo,
    };
}
void
HelloTriangleApplication::pickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    auto phys_devices    = instance->enumeratePhysicalDevices();

    if (phys_devices.size() == 0)
    {
        std::cout << "failed to find GPUs with Vulkan support :( \n";
    }

    for (auto const& device : phys_devices)
    {
        if (isDeviceSuitable(device))
        {
            physicalDevice =
                std::make_unique<vk::raii::PhysicalDevice>(std::move(device));
            break;
        }
    }

    if (physicalDevice == nullptr)
    {
        std::cerr << "failed to find GPU with required functionalities\n";
    }
}

QueueFamilyIndices
HelloTriangleApplication::findQueueFamilies(vk::raii::PhysicalDevice const& device)
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
        if (device.getSurfaceSupportKHR(i, **surface))
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
void
HelloTriangleApplication::createLogicalDevice()
{
    auto indices   = findQueueFamilies(*physicalDevice);
    float priority = 1.f;

    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(),
                                              indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies)
    {
        vk::DeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount       = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }
    vk::PhysicalDeviceFeatures physDeviceFeatures{};
    vk::DeviceCreateInfo deviceCreateInfo;
    if (enableValidationLayers)
    {
        deviceCreateInfo = {
            .queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfos.size()),
            .pQueueCreateInfos       = queueCreateInfos.data(),
            .enabledLayerCount       = static_cast<uint32_t>(validationLayers.size()),
            .ppEnabledLayerNames     = validationLayers.data(),
            .enabledExtensionCount   = static_cast<uint32_t>(deviceExtensions.size()),
            .ppEnabledExtensionNames = deviceExtensions.data(),
            .pEnabledFeatures        = &physDeviceFeatures,
        };
    }
    else
    {
        deviceCreateInfo = {
            .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
            .pQueueCreateInfos    = queueCreateInfos.data(),
            .enabledLayerCount    = 0,
            .pEnabledFeatures     = &physDeviceFeatures,
        };
    }

    device        = std::make_unique<vk::raii::Device>(*physicalDevice, deviceCreateInfo);
    graphicsQueue = std::make_unique<vk::raii::Queue>(
        device->getQueue(indices.graphicsFamily.value(), 0));
    presentQueue = std::make_unique<vk::raii::Queue>(
        device->getQueue(indices.presentFamily.value(), 0));
}

bool
HelloTriangleApplication::checkValidationLayerSupport()
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
