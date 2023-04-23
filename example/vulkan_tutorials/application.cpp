
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
    details.capabilities = device.getSurfaceCapabilitiesKHR(*surface);
    details.formats      = device.getSurfaceFormatsKHR(*surface);
    details.presentModes = device.getSurfacePresentModesKHR(*surface);

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
            static_cast<VkInstance>(*instance), window, nullptr, &_surface))
    {
        std::cerr << "Failed to create window surface :(\n";
        exit(-1);
    }

    surface = vk::raii::SurfaceKHR(instance, _surface);
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

    instance = vk::raii::Instance{context, createInfo};
}

void
HelloTriangleApplication::createRenderPass()
{
    vk::SubpassDependency dependency{
        .srcSubpass    = VK_SUBPASS_EXTERNAL,
        .dstSubpass    = 0,
        .srcStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput,
        .dstStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput,
        .srcAccessMask = vk::AccessFlagBits::eNoneKHR,
        .dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite,
    };
    vk::AttachmentDescription colorAttachment{
        .format         = imageFormat,
        .samples        = vk::SampleCountFlagBits::e1,
        .loadOp         = vk::AttachmentLoadOp::eClear,
        .storeOp        = vk::AttachmentStoreOp::eStore,
        .stencilLoadOp  = vk::AttachmentLoadOp::eDontCare,
        .stencilStoreOp = vk::AttachmentStoreOp::eDontCare,
        .initialLayout  = vk::ImageLayout::eUndefined,
        .finalLayout    = vk::ImageLayout::ePresentSrcKHR};

    vk::AttachmentReference colorAttachmentRef{
        .attachment = 0,
        .layout     = vk::ImageLayout::eColorAttachmentOptimal,
    };

    vk::SubpassDescription subpass{.pipelineBindPoint = vk::PipelineBindPoint::eGraphics,
                                   .colorAttachmentCount = 1,
                                   .pColorAttachments    = &colorAttachmentRef};

    vk::RenderPassCreateInfo renderPassInfo{.attachmentCount = 1,
                                            .pAttachments    = &colorAttachment,
                                            .subpassCount    = 1,
                                            .pSubpasses      = &subpass,
                                            .dependencyCount = 1,
                                            .pDependencies   = &dependency};

    renderPass = vk::raii::RenderPass(device, renderPassInfo);
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
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

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
    QueueFamilyIndices indices    = findQueueFamilies(physicalDevice);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(),
                                     indices.presentFamily.value()};
    vk::SwapchainCreateInfoKHR createInfo;

    if (indices.graphicsFamily != indices.presentFamily)
    {
        createInfo = {.surface               = *surface,
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
        createInfo = {.surface               = *surface,
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

    swapChain   = device.createSwapchainKHR(createInfo);
    auto images = swapChain.getImages();

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

        swapImageViews.emplace_back(device.createImageView(createInfo));
    }
}

vk::raii::ShaderModule
HelloTriangleApplication::createShaderModule(std::vector<std::byte> const& bytecode)
{
    vk::ShaderModuleCreateInfo createInfo{
        .codeSize = bytecode.size(),
        .pCode    = reinterpret_cast<uint32_t const*>(bytecode.data()),
    };

    return device.createShaderModule(createInfo);
}
void
HelloTriangleApplication::createGraphicsPipeline()
{
    auto vertshader = readFile("shaders/example/shader.vert.spv");
    auto fragshader = readFile("shaders/example/shader.frag.spv");

    auto vertModule{createShaderModule(vertshader)};
    auto fragModule{createShaderModule(fragshader)};

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

    std::vector<vk::PipelineShaderStageCreateInfo> shaderStages = {
        createVertShaderInfo,
        createFragShaderInfo,
    };

    std::vector<vk::DynamicState> dynamicStates = {
        vk::DynamicState::eViewport,
        vk::DynamicState::eScissor,
    };

    vk::PipelineDynamicStateCreateInfo dynamicStatesCreateInfo{
        .dynamicStateCount = static_cast<uint32_t>(dynamicStates.size()),
        .pDynamicStates    = dynamicStates.data(),
    };

    vk::PipelineVertexInputStateCreateInfo vertexInputInfo{
        .vertexBindingDescriptionCount   = 0,
        .pVertexBindingDescriptions      = nullptr,
        .vertexAttributeDescriptionCount = 0,
        .pVertexAttributeDescriptions    = nullptr};

    vk::PipelineInputAssemblyStateCreateInfo inputAssembly{
        .topology               = vk::PrimitiveTopology::eTriangleList,
        .primitiveRestartEnable = false};

    vk::Viewport viewport{.x        = 0.f,
                          .y        = 0.f,
                          .width    = (float)imageExtent.width,
                          .height   = (float)imageExtent.height,
                          .minDepth = 0.f,
                          .maxDepth = 1.f};
    vk::Rect2D scissor{
        .offset = {.x = 0, .y = 0},
        .extent = imageExtent,
    };

    vk::PipelineViewportStateCreateInfo viewportState{.viewportCount = 1,
                                                      .scissorCount  = 1};

    vk::PipelineRasterizationStateCreateInfo rasterizer{
        .depthClampEnable = false,
        .polygonMode      = vk::PolygonMode::eFill,
        .cullMode         = vk::CullModeFlagBits::eBack,
        .frontFace        = vk::FrontFace::eClockwise,
        .depthBiasEnable  = false,
        .lineWidth        = 1.0f,
    };

    vk::PipelineMultisampleStateCreateInfo multisampleing{
        .rasterizationSamples = vk::SampleCountFlagBits::e1,
        .sampleShadingEnable  = false,
    };

    vk::PipelineColorBlendAttachmentState colorBlendAttachment{
        .blendEnable    = false,
        .colorWriteMask = vk::ColorComponentFlagBits::eR |
                          vk::ColorComponentFlagBits::eG |
                          vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA,
    };

    vk::PipelineColorBlendStateCreateInfo colorBlending{
        .logicOpEnable   = false,
        .logicOp         = vk::LogicOp::eCopy,
        .attachmentCount = 1,
        .pAttachments    = &colorBlendAttachment,
    };

    vk::PipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayout = device.createPipelineLayout(pipelineLayoutInfo);

    vk::GraphicsPipelineCreateInfo pipelineInfo{
        .stageCount          = 2,
        .pStages             = shaderStages.data(),
        .pVertexInputState   = &vertexInputInfo,
        .pInputAssemblyState = &inputAssembly,
        .pViewportState      = &viewportState,
        .pRasterizationState = &rasterizer,
        .pMultisampleState   = &multisampleing,
        .pColorBlendState    = &colorBlending,
        .pDynamicState       = &dynamicStatesCreateInfo,
        .layout              = *pipelineLayout,
        .renderPass          = *renderPass,
        .subpass             = 0,
        .basePipelineHandle  = nullptr,
        .basePipelineIndex   = -1,
    };

    graphicsPipeline =
        device.createGraphicsPipeline(vk::raii::PipelineCache{nullptr}, pipelineInfo);
}
void
HelloTriangleApplication::pickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    auto phys_devices    = instance.enumeratePhysicalDevices();

    if (phys_devices.size() == 0)
    {
        std::cout << "failed to find GPUs with Vulkan support :( \n";
    }

    for (auto const& device : phys_devices)
    {
        if (isDeviceSuitable(device))
        {
            physicalDevice = device;
            return;
        }
    }

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
void
HelloTriangleApplication::createLogicalDevice()
{
    auto indices   = findQueueFamilies(physicalDevice);
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

    device = vk::raii::Device(physicalDevice, deviceCreateInfo);

    graphicsQueue = vk::raii::Queue(device.getQueue(indices.graphicsFamily.value(), 0));
    presentQueue  = vk::raii::Queue(device.getQueue(indices.presentFamily.value(), 0));
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

void
HelloTriangleApplication::createFramebuffers()
{
    swapchainFramebuffers.reserve(swapImageViews.size());

    for (std::size_t i = 0; i < swapImageViews.size(); i++)
    {
        vk::FramebufferCreateInfo framebufferInfo{.renderPass      = *renderPass,
                                                  .attachmentCount = 1,
                                                  .pAttachments = &(*swapImageViews[i]),
                                                  .width        = imageExtent.width,
                                                  .height       = imageExtent.height,
                                                  .layers       = 1};
        swapchainFramebuffers.emplace_back(device, framebufferInfo, nullptr);
    }
}

void
HelloTriangleApplication::createCommandPool()
{
    auto indices = findQueueFamilies(physicalDevice);

    vk::CommandPoolCreateInfo poolInfo{
        .flags            = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
        .queueFamilyIndex = indices.graphicsFamily.value()};

    commandPool = device.createCommandPool(poolInfo);
}

void
HelloTriangleApplication::createCommandBuffer()
{

    vk::CommandBufferAllocateInfo allocInfo{
        .commandPool        = *commandPool,
        .level              = vk::CommandBufferLevel::ePrimary,
        .commandBufferCount = 1,
    };
    vk::CommandBuffer buffer;
    auto buffers  = device.allocateCommandBuffers(allocInfo);
    commandBuffer = std::move(buffers[0]);
}
void
HelloTriangleApplication::recordCommandBuffer(vk::raii::CommandBuffer& buffer,
                                              uint32_t imageIndex)
{
    vk::CommandBufferBeginInfo beginInfo{
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

    vk::Viewport viewport{.x        = 0.f,
                          .y        = 0.f,
                          .width    = (float)imageExtent.width,
                          .height   = (float)imageExtent.height,
                          .minDepth = 0.f,
                          .maxDepth = 1.f};
    vk::ArrayProxy<vk::Viewport> proxy{viewport};

    buffer.setViewport(0, proxy);

    vk::ArrayProxy scissors{vk::Rect2D{.offset = {0, 0}, .extent = imageExtent}};

    buffer.setScissor(0, scissors);

    buffer.draw(3, 1, 0, 0);

    buffer.endRenderPass();

    buffer.end();
}

void
HelloTriangleApplication::drawFrame()
{
    device.waitForFences({*inFlight}, true, std::numeric_limits<uint64_t>::max());
    device.resetFences({*inFlight});

    uint32_t imageIndex;
    commandBuffer.reset();
    {
        vkAcquireNextImageKHR(
            *device, *swapChain, UINT64_MAX, *imageAvailable, nullptr, &imageIndex);
        recordCommandBuffer(commandBuffer, imageIndex);
    }

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

    vk::PresentInfoKHR presentInfo{.waitSemaphoreCount = 1,
                                   .pWaitSemaphores    = &(*renderFinished),
                                   .swapchainCount     = 1,
                                   .pSwapchains        = &(*swapChain),
                                   .pImageIndices      = &imageIndex,
                                   .pResults           = nullptr};

    presentQueue.presentKHR(presentInfo);
}

void
HelloTriangleApplication::createSyncObjects()
{
    vk::SemaphoreCreateInfo semaphoreInfo{};

    vk::FenceCreateInfo fenceInfo{.flags = vk::FenceCreateFlagBits::eSignaled};

    imageAvailable = vk::raii::Semaphore(device, semaphoreInfo);
    renderFinished = vk::raii::Semaphore(device, semaphoreInfo);
    inFlight       = vk::raii::Fence(device, fenceInfo);
}