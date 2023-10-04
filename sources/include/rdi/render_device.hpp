
#pragma once

#include "rdi_export.hpp"

#include "rdi/common.hpp"

#include "rdi/viewport.hpp"

#include <string>
#include <string_view>
#include <memory>

namespace ivd
{
namespace rdi
{

class RDI_API render_device : non_copyable
{
public:
    render_device(render_device&&)            = default;
    render_device& operator=(render_device&&) = default;

public:
    render_device(std::string_view title) : m_title(title) {}
    virtual ~render_device() {}

public:
    virtual void initialize() = 0;
    virtual void shutdown()   = 0;

public:
    virtual std::unique_ptr<viewport> create_viewport() = 0;

protected:
    std::string m_title;
};
} // namespace rdi

} // namespace ivd