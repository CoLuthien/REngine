
#pragma once

#include "HAL/platforms.hpp"

#include <glm/glm.hpp>

#include <vulkan/vulkan_raii.hpp>

#include <cstdint>
#include <cstddef>
#include <array>

struct Vertex
{
    glm::vec2 pos{};
    glm::vec3 color{};

    static vk::VertexInputBindingDescription getBindingDescription()
    {
        return vk::VertexInputBindingDescription{
            .binding   = 0,
            .stride    = sizeof(Vertex),
            .inputRate = vk::VertexInputRate::eVertex,
        };
    }

    static std::array<vk::VertexInputAttributeDescription, 2> getAttributeDescriptions()
    {
        static constexpr vk::VertexInputAttributeDescription positionAttrib{
            .location = 0,
            .binding  = 0,
            .format   = vk::Format::eR32G32Sfloat,
            .offset   = offsetof(Vertex, pos),
        };
        static constexpr auto colorAttrib = vk::VertexInputAttributeDescription{
            .location = 1,
            .binding  = 0,
            .format   = vk::Format::eR32G32B32Sfloat,
            .offset   = offsetof(Vertex, color),
        };

        return {positionAttrib, colorAttrib};
    }
};
