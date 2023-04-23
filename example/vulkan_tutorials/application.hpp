
#pragma once

#include "HAL/platforms.hpp"

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

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

static constexpr auto WIDTH  = 800;
static constexpr auto HEIGHT = 600;

const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() const
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails
{
    vk::SurfaceCapabilitiesKHR capabilities;
    std::vector<vk::SurfaceFormatKHR> formats;
    std::vector<vk::PresentModeKHR> presentModes;
};

class HelloTriangleApplication
{
public:
private:
    GLFWwindow* window;

    vk::Extent2D imageExtent;
    vk::Format imageFormat;
    
    vk::raii::Instance instance{nullptr};
    vk::raii::PhysicalDevice physicalDevice{nullptr};
    vk::raii::SurfaceKHR surface{nullptr};
    vk::raii::Device device{nullptr};
    vk::raii::Queue graphicsQueue{nullptr};
    vk::raii::Queue presentQueue{nullptr};
    vk::raii::SwapchainKHR swapChain{nullptr};
    std::vector<vk::Image> swapImages;
    std::vector<vk::raii::ImageView> swapImageViews;
    vk::raii::RenderPass renderPass{nullptr};
    vk::raii::PipelineLayout pipelineLayout{nullptr};
    vk::raii::Pipeline graphicsPipeline{nullptr};
    std::vector<vk::raii::Framebuffer> swapchainFramebuffers;
    vk::raii::CommandPool commandPool{nullptr};
    vk::raii::CommandBuffer commandBuffer{nullptr};
    vk::raii::Fence inFlight{nullptr};
    vk::raii::Semaphore imageAvailable{nullptr};
    vk::raii::Semaphore renderFinished{nullptr};

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
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createCommandBuffer();
        createSyncObjects();
    }

    void createSyncObjects();
    void recordCommandBuffer(vk::raii::CommandBuffer& buffer, uint32_t imageIndex);
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

    vk::SurfaceFormatKHR chooseSwapSurfaceFormat(
        std::vector<vk::SurfaceFormatKHR> const& formats);
    vk::PresentModeKHR chooseSwapPresentMode(
        std::vector<vk::PresentModeKHR> const& modes);
    vk::Extent2D chooseSwapExtent(vk::SurfaceCapabilitiesKHR const& capabilities);

private:
    bool isDeviceSuitable(vk::raii::PhysicalDevice const& device);
    SwapChainSupportDetails querySwapChainSupport(vk::raii::PhysicalDevice const& device);
    QueueFamilyIndices findQueueFamilies(vk::raii::PhysicalDevice const& device);

private:
    void createInstance();
    bool checkValidationLayerSupport();
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
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};