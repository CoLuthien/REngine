
#pragma once

#include "rdi_export.hpp"

#include "rdi_buffers.hpp"

namespace ivd
{
namespace rdi
{
class RDI_API rdi_resource
{
public:
    virtual void initialize() {}
};

class RDI_API index_buffer : public rdi_resource
{
public:
public:
    std::weak_ptr<buffer> m_buffer;
};

class RDI_API vertex_buffer : public rdi_resource
{
public:
public:
    std::weak_ptr<buffer> m_buffer;
};

} // namespace rdi
} // namespace ivd
