

#include "core_object/object.hpp"
#include "core_object/class.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

class HelloTriangleApplication
{
public:
    static constexpr uint32_t WIDTH  = 800;
    static constexpr uint32_t HEIGHT = 600;

public:
    void run()
    {
        InitWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initVulkan() {}
    void InitWindow()
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void mainLoop() {}

    void cleanup() {}

private:
    GLFWwindow* m_window;
};

int
main()
{
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
