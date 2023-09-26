
#pragma once

#include "rdi_export.hpp"

#include <string_view>

namespace ivd
{
namespace rdi
{

class RDI_API rdi_generic
{
public:
    rdi_generic(std::string_view title_name) : m_title_name(title_name) {}
    virtual ~rdi_generic() {}

public:
    virtual void initialize() = 0;
    virtual void shutdown()   = 0;

protected:
    std::string m_title_name;
};
} // namespace rdi

} // namespace ivd