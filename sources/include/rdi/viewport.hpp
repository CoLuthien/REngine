
#pragma once

#include "utils/non_copyable.hpp"
#include "rdi_export.hpp"

#include <glfwpp/glfwpp.h>
#include <memory>

namespace ivd::rdi
{

class RDI_API viewport : non_copyable
{
public:
    viewport(viewport&&)            = default;
    viewport& operator=(viewport&&) = default;

public:
    viewport(std::weak_ptr<glfw::Window> window_surface);
};

} // namespace ivd::rdi