
#pragma once

#include "rdi_export.hpp"
#include "section/section_interface.hpp"

#include <memory>

namespace ivd::rdi
{

class RDI_API section : public section_interface
{
public:
    section() = default;

public:
    virtual bool initialize() override;

private:
    class vk_section;
    class gl_section;
    std::shared_ptr<class vk_section> m_vk;
    std::shared_ptr<class gl_section> m_gl;
};

} // namespace ivd::rdi