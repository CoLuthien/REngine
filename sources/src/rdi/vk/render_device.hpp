
#pragma once

#include "rdi_export.hpp"
#include "rdi/render_device.hpp"

#include "rdi/common.hpp"
#include "common.hpp"

#include <vulkan/vulkan_raii.hpp>

namespace ivd::rdi
{

class RDI_API vk_render_device : public render_device
{
public:
    vk_render_device(std::string_view title);

public:
    virtual void initialize() override;

private:
    vk::raii::Instance m_instance{nullptr};
};

} // namespace ivd::rdi