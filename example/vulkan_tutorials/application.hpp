
#pragma once

#include "primitives.hpp"

#include "HAL/platforms.hpp"

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include <vulkan/vulkan_raii.hpp>
#include <GLFW/glfw3.h>

#include <fstream>
#include <cstdint>   // Necessary for uint32_t
#include <limits>    // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp
#include <cstring>
#include <iostream>
#include <optional>
#include <vector>
#include <set>
#include <memory>
#include <span>

static constexpr auto WIDTH            = 800;
static constexpr auto HEIGHT           = 600;
static constexpr auto ConcurrentFrames = 2;

const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

const std::vector<Vertex> vertices = {{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                                      {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                                      {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
                                      {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};

const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0};

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> transferFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() const
    {
        return graphicsFamily.has_value() && presentFamily.has_value() &&
               transferFamily.has_value();
    }
};

struct SwapChainSupportDetails
{
    vk::SurfaceCapabilitiesKHR        capabilities;
    std::vector<vk::SurfaceFormatKHR> formats;
    std::vector<vk::PresentModeKHR>   presentModes;
};

class TriangleApplication
{
public:
    bool framebufferResized = false;

private:
    vk::raii::Buffer createBuffer(vk::DeviceSize             size,
                                  vk::BufferUsageFlagBits    usage,
                                  vk::MemoryPropertyFlagBits properties,
                                  vk::raii::DeviceMemory&    bufferMemory,
                                  std::span<uint32_t>        sharedIndices);
    void copyBuffer(vk::raii::Buffer& fromBuffer, vk::raii::Buffer& toBuffer, vk::DeviceSize size);

private:
    GLFWwindow* window;

    vk::Extent2D imageExtent;
    vk::Format   imageFormat;
    vk::Viewport viewport;
    vk::Rect2D   scissor;

    vk::raii::Instance                   instance{nullptr};
    vk::raii::PhysicalDevice             physicalDevice{nullptr};
    vk::raii::SurfaceKHR                 surface{nullptr};
    vk::raii::Device                     device{nullptr};
    vk::raii::Queue                      graphicsQueue{nullptr};
    vk::raii::Queue                      presentQueue{nullptr};
    vk::raii::Queue                      transferQueue{nullptr};
    vk::raii::SwapchainKHR               swapChain{nullptr};
    std::vector<vk::Image>               swapImages;
    std::vector<vk::raii::ImageView>     swapImageViews;
    vk::raii::RenderPass                 renderPass{nullptr};
    vk::raii::DescriptorSetLayout        descriptorSetLayout{nullptr};
    vk::raii::DescriptorPool             descriptorPool{nullptr};
    vk::raii::PipelineLayout             pipelineLayout{nullptr};
    vk::raii::Pipeline                   graphicsPipeline{nullptr};
    std::vector<vk::raii::Framebuffer>   swapchainFramebuffers;
    vk::raii::CommandPool                commandPool{nullptr};
    vk::raii::CommandPool                transferCommands{nullptr};
    std::vector<vk::raii::DescriptorSet> descriptorSets;

    vk::raii::Buffer       vertexBuffer{nullptr};
    vk::raii::DeviceMemory vertexBufferMemory{nullptr};

    vk::raii::Buffer       indexBuffer{nullptr};
    vk::raii::DeviceMemory indexBufferMemory{nullptr};

    std::vector<vk::raii::Buffer>       uniformBuffers;
    std::vector<vk::raii::DeviceMemory> uniformBuffersMemory;
    std::vector<void*>                  uniformBuffersMapped;

    std::vector<vk::raii::CommandBuffer> commandBuffers;
    std::vector<vk::raii::Fence>         inFlights;
    std::vector<vk::raii::Semaphore>     imageAvailables;
    std::vector<vk::raii::Semaphore>     renderFinishes;

    uint32_t currentFrameIdx = 0;

public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow();
    void initVulkan()
    {
        createInstance();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();

        createRenderPass();
        createDescriptorSetLayout();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createVertexBuffer();
        createIndexBuffer();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();

        createCommandBuffer();
        createSyncObjects();
    }
    void updateUniformBuffer(uint32_t frameIdx);

    void     createDescriptorPool();
    uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlagBits properties);

    void createDescriptorSetLayout();
    void createDescriptorSets();
    void createUniformBuffers();

    void createSyncObjects();
    void recordCommandBuffer(vk::raii::CommandBuffer& buffer, uint32_t imageIndex);
    void createIndexBuffer();
    void createVertexBuffer();
    void createCommandBuffer();
    void createCommandPool();
    void createFramebuffers();
    void createRenderPass();
    void createImageViews();
    void createSurface();
    void createSwapChain();
    void createGraphicsPipeline();
    vk::raii::ShaderModule createShaderModule(std::vector<std::byte> const& bytecode);

    void createLogicalDevice();
    void pickPhysicalDevice();
    bool checkDeviceExtensionSupport(vk::raii::PhysicalDevice const& device);

    vk::SurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<vk::SurfaceFormatKHR> const& formats);
    vk::PresentModeKHR   chooseSwapPresentMode(std::vector<vk::PresentModeKHR> const& modes);
    vk::Extent2D         chooseSwapExtent(vk::SurfaceCapabilitiesKHR const& capabilities);

private:
    bool                    isDeviceSuitable(vk::raii::PhysicalDevice const& device);
    SwapChainSupportDetails querySwapChainSupport(vk::raii::PhysicalDevice const& device);
    QueueFamilyIndices      findQueueFamilies(vk::raii::PhysicalDevice const& device);

private:
    void                     createInstance();
    bool                     checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();

    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            drawFrame();
        }
        device.waitIdle();
    }

    void drawFrame();

    void cleanup()
    {
        cleanupSwapChain();

        glfwDestroyWindow(window);
        glfwTerminate();
    }
    void recreateSwapChain();
    void cleanupSwapChain();
};