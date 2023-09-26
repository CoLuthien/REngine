
#include "application.hpp"
#include <iostream>
#include "meta/vulkan_helper.hpp"

vk::raii::Buffer
TriangleApplication::createBuffer(vk::DeviceSize             size,
                                  vk::BufferUsageFlagBits    usage,
                                  vk::MemoryPropertyFlagBits properties,
                                  vk::raii::DeviceMemory&    bufferMemory,
                                  std::span<uint32_t>        sharedIndices)
{
    vk::BufferCreateInfo createInfo = {
        .size  = size,
        .usage = usage,
        .sharingMode =
            sharedIndices.size() > 1 ? vk::SharingMode::eConcurrent : vk::SharingMode::eExclusive,
        .queueFamilyIndexCount = static_cast<uint32_t>(sharedIndices.size()),
        .pQueueFamilyIndices   = sharedIndices.data()};

    vk::raii::Buffer buffer{nullptr};
    try
    {
        buffer = device.createBuffer(createInfo);
    }
    catch (std::exception const& e)
    {
        throw std::runtime_error{"failed to create buffer!"};
    }

    auto reqs = buffer.getMemoryRequirements();

    vk::MemoryAllocateInfo allocInfo = {.allocationSize = reqs.size,
                                        .memoryTypeIndex =
                                            findMemoryType(reqs.memoryTypeBits, properties)};

    try
    {
        bufferMemory = device.allocateMemory(allocInfo);
    }
    catch (std::exception const& e)
    {
        throw std::runtime_error{"failed to allocate memory"};
    }

    buffer.bindMemory(*bufferMemory, 0);

    return buffer;
}

static VKAPI_ATTR vk::Bool32 VKAPI_CALL
                  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
                                VkDebugUtilsMessageTypeFlagsEXT             messageType,
                                VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData,
                                void*                                       pUserData)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return false;
}

static std::vector<std::byte>
readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        exit(-1);
    }
    std::size_t            fileSize = file.tellg();
    std::vector<std::byte> buffer(fileSize);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    file.close();

    return buffer;
}

void
TriangleApplication::createInstance()
{

    if (enableValidationLayers && !checkValidationLayerSupport())
    {
        std::cout << "validation layers requested, but not available!\n";
        exit(-1);
    }

    vk::ApplicationInfo appInfo = {.pNext              = nullptr,
                                   .pApplicationName   = "Hello Triangle",
                                   .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                                   .pEngineName        = "No Engine",
                                   .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
                                   .apiVersion         = VK_API_VERSION_1_0};

    auto                                 extensions = getRequiredExtensions();
    vk::raii::Context                    context;
    vk::InstanceCreateInfo               createInfo;
    vk::DebugUtilsMessengerCreateInfoEXT createDebugInfo;
    if (enableValidationLayers)
    {
        createDebugInfo = {.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
                                              vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                                              vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose,
                           .messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                                          vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                                          vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
                           .pfnUserCallback = &debugCallback,
                           .pUserData       = nullptr};

        createInfo = {.pNext               = &(VkDebugUtilsMessengerCreateInfoEXT&)createDebugInfo,
                      .pApplicationInfo    = &appInfo,
                      .enabledLayerCount   = static_cast<uint32_t>(validationLayers.size()),
                      .ppEnabledLayerNames = validationLayers.data(),
                      .enabledExtensionCount   = static_cast<uint32_t>(extensions.size()),
                      .ppEnabledExtensionNames = extensions.data()};
    }
    else
    {
        createInfo = {.pNext                   = nullptr,
                      .pApplicationInfo        = &appInfo,
                      .enabledLayerCount       = 0,
                      .ppEnabledLayerNames     = nullptr,
                      .enabledExtensionCount   = static_cast<uint32_t>(extensions.size()),
                      .ppEnabledExtensionNames = extensions.data()};
    }
    instance = vk::raii::Instance{context, createInfo};
}

void
TriangleApplication::createSurface()
{
    VkSurfaceKHR _surface;
    if (glfwCreateWindowSurface(static_cast<VkInstance>(*instance), window, nullptr, &_surface))
    {
        std::cerr << "Failed to create window surface :(\n";
        exit(-1);
    }

    surface = vk::raii::SurfaceKHR(instance, _surface);
}

void
TriangleApplication::pickPhysicalDevice()
{
    auto phys_devices = instance.enumeratePhysicalDevices();

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

void
TriangleApplication::createLogicalDevice()
{
    auto indices = findQueueFamilies(physicalDevice);

    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t>                     uniqueQueueFamilies = {indices.graphicsFamily.value(),
                                                                  indices.presentFamily.value(),
                                                                  indices.transferFamily.value()};

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
    vk::DeviceCreateInfo       deviceCreateInfo;
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
            .queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfos.size()),
            .pQueueCreateInfos       = queueCreateInfos.data(),
            .enabledLayerCount       = 0,
            .enabledExtensionCount   = static_cast<uint32_t>(deviceExtensions.size()),
            .ppEnabledExtensionNames = deviceExtensions.data(),
            .pEnabledFeatures        = &physDeviceFeatures,
        };
    }

    device = vk::raii::Device(physicalDevice, deviceCreateInfo);

    graphicsQueue = vk::raii::Queue(device.getQueue(indices.graphicsFamily.value(), 0));
    presentQueue  = vk::raii::Queue(device.getQueue(indices.presentFamily.value(), 0));
    transferQueue = vk::raii::Queue(device.getQueue(indices.transferFamily.value(), 0));
}

void
TriangleApplication::createSwapChain()
{
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

    vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    vk::PresentModeKHR   presentMode   = chooseSwapPresentMode(swapChainSupport.presentModes);
    vk::Extent2D         extent        = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 &&
        imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }
    QueueFamilyIndices indices    = findQueueFamilies(physicalDevice);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
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
    createInfo.setClipped(true);
    createInfo.setOldSwapchain(nullptr);

    swapChain   = device.createSwapchainKHR(createInfo);
    auto images = swapChain.getImages();

    swapImages  = images;
    imageFormat = surfaceFormat.format;
    imageExtent = extent;
}

void
TriangleApplication::createImageViews()
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

void
TriangleApplication::createRenderPass()
{
    vk::SubpassDependency dependency{
        .srcSubpass    = VK_SUBPASS_EXTERNAL,
        .dstSubpass    = 0,
        .srcStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput,
        .dstStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput,
        .srcAccessMask = vk::AccessFlagBits::eNoneKHR,
        .dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite,
    };
    vk::AttachmentDescription colorAttachment{.format         = imageFormat,
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

    vk::SubpassDescription subpass{.pipelineBindPoint    = vk::PipelineBindPoint::eGraphics,
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

void
TriangleApplication::createGraphicsPipeline()
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

    auto bindingDescription    = Vertex::getBindingDescription();
    auto attributeDescriptions = Vertex::getAttributeDescriptions();

    vk::PipelineVertexInputStateCreateInfo vertexInputInfo{
        .vertexBindingDescriptionCount   = 1,
        .pVertexBindingDescriptions      = &bindingDescription,
        .vertexAttributeDescriptionCount = attributeDescriptions.size(),
        .pVertexAttributeDescriptions    = attributeDescriptions.data()};

    vk::PipelineInputAssemblyStateCreateInfo inputAssembly{
        .topology = vk::PrimitiveTopology::eTriangleList, .primitiveRestartEnable = false};

    viewport = vk::Viewport{
        .x = 0.f, .y = 0.f, .width = 800.f, .height = 600.f, .minDepth = 0.f, .maxDepth = 1.f};
    scissor = vk::Rect2D{
        .offset = {.x = 0, .y = 0},
        .extent = imageExtent,
    };

    vk::PipelineViewportStateCreateInfo viewportState{
        .viewportCount = 1,
        .pViewports    = &viewport,
        .scissorCount  = 1,
        .pScissors     = &scissor,
    };

    vk::PipelineRasterizationStateCreateInfo rasterizer{
        .depthClampEnable = false,
        .polygonMode      = vk::PolygonMode::eFill,
        .cullMode         = vk::CullModeFlagBits::eBack,
        .frontFace        = vk::FrontFace::eCounterClockwise,
        .depthBiasEnable  = false,
        .lineWidth        = 1.0f,
    };

    vk::PipelineMultisampleStateCreateInfo multisampleing{
        .rasterizationSamples = vk::SampleCountFlagBits::e1,
        .sampleShadingEnable  = false,
    };

    vk::PipelineColorBlendAttachmentState colorBlendAttachment{
        .blendEnable    = false,
        .colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
                          vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA,
    };

    vk::PipelineColorBlendStateCreateInfo colorBlending{
        .logicOpEnable   = false,
        .logicOp         = vk::LogicOp::eCopy,
        .attachmentCount = 1,
        .pAttachments    = &colorBlendAttachment,
    };

    vk::PipelineLayoutCreateInfo pipelineLayoutInfo{
        .setLayoutCount = 1,
        .pSetLayouts    = &*descriptorSetLayout,
    };
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
    };

    graphicsPipeline = device.createGraphicsPipeline(nullptr, pipelineInfo);
}

void
TriangleApplication::createFramebuffers()
{
    swapchainFramebuffers.reserve(swapImageViews.size());

    for (std::size_t i = 0; i < swapImageViews.size(); i++)
    {
        vk::FramebufferCreateInfo framebufferInfo{.renderPass      = *renderPass,
                                                  .attachmentCount = 1,
                                                  .pAttachments    = &(*swapImageViews[i]),
                                                  .width           = imageExtent.width,
                                                  .height          = imageExtent.height,
                                                  .layers          = 1};
        swapchainFramebuffers.emplace_back(device, framebufferInfo, nullptr);
    }
}

void
TriangleApplication::createCommandPool()
{
    auto indices = findQueueFamilies(physicalDevice);

    vk::CommandPoolCreateInfo poolInfo{.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
                                       .queueFamilyIndex = indices.graphicsFamily.value()};

    commandPool = device.createCommandPool(poolInfo);

    vk::CommandPoolCreateInfo transferPoolInfo{
        .flags = meta::mask_as_enum<vk::CommandPoolCreateFlagBits>(
            vk::CommandPoolCreateFlagBits::eResetCommandBuffer |
            vk::CommandPoolCreateFlagBits::eTransient),
        .queueFamilyIndex = indices.transferFamily.value()};
    transferCommandPool = device.createCommandPool(transferPoolInfo);
}

uint32_t
TriangleApplication::findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlagBits properties)
{
    auto memProperties = physicalDevice.getMemoryProperties();
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void
TriangleApplication::copyBuffer(vk::raii::Buffer& fromBuffer,
                                vk::raii::Buffer& toBuffer,
                                vk::DeviceSize    size)
{
    vk::CommandBufferAllocateInfo allocInfo = {.commandPool = *transferCommandPool,
                                               .level       = vk::CommandBufferLevel::ePrimary,
                                               .commandBufferCount = 1};

    auto&& transferCommands = device.allocateCommandBuffers(allocInfo);
    auto&  transferCommand  = transferCommands[0];

    vk::CommandBufferBeginInfo beginInfo = {
        .flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit,
    };

    transferCommand.begin(beginInfo);

    vk::BufferCopy copyInfo = {.srcOffset = 0, .dstOffset = 0, .size = size};

    transferCommand.copyBuffer(*fromBuffer, *toBuffer, copyInfo);

    transferCommand.end();

    vk::SubmitInfo submitInfo = {
        .commandBufferCount = 1,
        .pCommandBuffers    = &*transferCommand,
    };

    transferQueue.submit(submitInfo);
    transferQueue.waitIdle();
    transferCommands.clear();
}

void
TriangleApplication::createDescriptorPool()
{
    vk::DescriptorPoolSize       poolSize   = {.type            = vk::DescriptorType::eUniformBuffer,
                                               .descriptorCount = ConcurrentFrames};
    vk::DescriptorPoolCreateInfo createInfo = {
        .flags         = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet,
        .maxSets       = static_cast<uint32_t>(ConcurrentFrames),
        .poolSizeCount = 1,
        .pPoolSizes    = &poolSize,
    };

    descriptorPool = device.createDescriptorPool(createInfo);
}
void
TriangleApplication::createDescriptorSetLayout()
{
    vk::DescriptorSetLayoutBinding uboLayout = {
        .binding            = 0,
        .descriptorType     = vk::DescriptorType::eUniformBuffer,
        .descriptorCount    = 1,
        .stageFlags         = vk::ShaderStageFlagBits::eVertex,
        .pImmutableSamplers = nullptr,
    };
    vk::DescriptorSetLayoutCreateInfo createInfo = {
        .bindingCount = 1,
        .pBindings    = &uboLayout,
    };

    descriptorSetLayout = device.createDescriptorSetLayout(createInfo);
}

void
TriangleApplication::createDescriptorSets()
{
    std::vector<vk::DescriptorSetLayout> layouts(ConcurrentFrames, *descriptorSetLayout);

    vk::DescriptorSetAllocateInfo allocInfo{.descriptorPool     = *descriptorPool,
                                            .descriptorSetCount = ConcurrentFrames,
                                            .pSetLayouts        = layouts.data()};

    descriptorSets.reserve(ConcurrentFrames);
    descriptorSets = device.allocateDescriptorSets(allocInfo);

    for (size_t i = 0; i < ConcurrentFrames; i++)
    {
        vk::DescriptorBufferInfo bufferInfo{
            .buffer = *uniformBuffers[i],
            .offset = 0,
            .range  = sizeof(UniformBufferObject),
        };

        vk::WriteDescriptorSet descriptorWrite{
            .dstSet           = *descriptorSets[i],
            .dstBinding       = 0,
            .dstArrayElement  = 0,
            .descriptorCount  = 1,
            .descriptorType   = vk::DescriptorType::eUniformBuffer,
            .pImageInfo       = nullptr,
            .pBufferInfo      = &bufferInfo,
            .pTexelBufferView = nullptr,
        };

        device.updateDescriptorSets(descriptorWrite, {});
    }
}

void
TriangleApplication::createUniformBuffers()
{
    static constexpr auto bufferSize = sizeof(UniformBufferObject);

    auto familyIndices = findQueueFamilies(physicalDevice);

    for (std::size_t i = 0; i < ConcurrentFrames; ++i)
    {
        vk::raii::DeviceMemory memory{nullptr};

        auto buffer = createBuffer(bufferSize,
                                   vk::BufferUsageFlagBits::eUniformBuffer,
                                   meta::mask_as_enum<vk::MemoryPropertyFlagBits>(
                                       vk::MemoryPropertyFlagBits::eHostVisible |
                                       vk::MemoryPropertyFlagBits::eHostCoherent),
                                   memory,
                                   {&familyIndices.graphicsFamily.value(), 1});

        auto* mappedMemory = memory.mapMemory(0, bufferSize);

        uniformBuffers.emplace_back(std::move(buffer));
        uniformBuffersMemory.emplace_back(std::move(memory));
        uniformBuffersMapped.emplace_back(std::move(mappedMemory));
    }
}

void
TriangleApplication::createIndexBuffer()
{

    auto familyIndices = findQueueFamilies(physicalDevice);

    auto bufferSize = sizeof(indices[0]) * indices.size();

    vk::raii::DeviceMemory stagingMemory{nullptr};
    std::array             stageIndices = {familyIndices.graphicsFamily.value(),
                                           familyIndices.transferFamily.value()};

    auto stagingBuffer = createBuffer(
        bufferSize,
        vk::BufferUsageFlagBits::eTransferSrc,
        meta::mask_as_enum<vk::MemoryPropertyFlagBits>(vk::MemoryPropertyFlagBits::eHostVisible |
                                                       vk::MemoryPropertyFlagBits::eHostCoherent),
        stagingMemory,
        {stageIndices.data(), 2});

    auto* data = stagingMemory.mapMemory(0, bufferSize);
    std::memcpy(data, indices.data(), bufferSize);
    stagingMemory.unmapMemory();

    indexBuffer = createBuffer(
        bufferSize,
        meta::mask_as_enum<vk::BufferUsageFlagBits>(vk::BufferUsageFlagBits::eTransferDst |
                                                    vk::BufferUsageFlagBits::eIndexBuffer),
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        indexBufferMemory,
        {&familyIndices.graphicsFamily.value(), 1});

    copyBuffer(stagingBuffer, indexBuffer, bufferSize);
}
void
TriangleApplication::createVertexBuffer()
{

    auto Indices = findQueueFamilies(physicalDevice);

    auto bufferSize = sizeof(vertices[0]) * vertices.size();

    vk::raii::DeviceMemory stagingMemory{nullptr};
    std::array stageIndices = {Indices.graphicsFamily.value(), Indices.transferFamily.value()};

    auto stagingBuffer = createBuffer(
        bufferSize,
        vk::BufferUsageFlagBits::eTransferSrc,
        meta::mask_as_enum<vk::MemoryPropertyFlagBits>(vk::MemoryPropertyFlagBits::eHostVisible |
                                                       vk::MemoryPropertyFlagBits::eHostCoherent),
        stagingMemory,
        {stageIndices.data(), 2});

    auto* data = stagingMemory.mapMemory(0, bufferSize);
    std::memcpy(data, vertices.data(), bufferSize);
    stagingMemory.unmapMemory();

    vertexBuffer = createBuffer(
        bufferSize,
        meta::mask_as_enum<vk::BufferUsageFlagBits>(vk::BufferUsageFlagBits::eTransferDst |
                                                    vk::BufferUsageFlagBits::eVertexBuffer),
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        vertexBufferMemory,
        {&Indices.graphicsFamily.value(), 1});

    copyBuffer(stagingBuffer, vertexBuffer, bufferSize);
}
void
TriangleApplication::createCommandBuffer()
{

    vk::CommandBufferAllocateInfo allocInfo{
        .pNext              = nullptr,
        .commandPool        = *commandPool,
        .level              = vk::CommandBufferLevel::ePrimary,
        .commandBufferCount = ConcurrentFrames,
    };
    commandBuffers = device.allocateCommandBuffers(allocInfo);
}

void
TriangleApplication::createSyncObjects()
{
    vk::SemaphoreCreateInfo semaphoreInfo{};

    vk::FenceCreateInfo fenceInfo{.flags = vk::FenceCreateFlagBits::eSignaled};

    for (auto i = 0; i < ConcurrentFrames; i++)
    {
        imageAvailables.emplace_back(device, semaphoreInfo);
        renderFinishes.emplace_back(device, semaphoreInfo);
        inFlights.emplace_back(device, fenceInfo);
    }

    // renderFinished = vk::raii::Semaphore(device, semaphoreInfo);
    // inFlight       = vk::raii::Fence(device, fenceInfo);
}