
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
private:
    std::unique_ptr<vk::raii::Instance> instance;
    std::unique_ptr<vk::raii::PhysicalDevice> physicalDevice;
    std::unique_ptr<vk::raii::Device> device;
    std::unique_ptr<vk::raii::Queue> graphicsQueue;
    std::unique_ptr<vk::raii::Queue> presentQueue;
    std::unique_ptr<vk::raii::SurfaceKHR> surface;

    std::unique_ptr<vk::raii::SwapchainKHR> swapChain;
    vk::Extent2D imageExtent;
    vk::Format imageFormat;

    std::vector<vk::Image> swapImages;
    std::vector<vk::raii::ImageView> swapImageViews;
    GLFWwindow* window;

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
        createGraphicsPipeline();
    }

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
        }
    }

    void cleanup()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};