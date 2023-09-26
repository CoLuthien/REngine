
#pragma once

#include "rdi_export.hpp"

#include "rdi/rdi_commons.hpp"

namespace ivd
{
namespace rdi
{

class RDI_API buffer
{
public:
    buffer()                         = delete;  // default ctor
    buffer(buffer const&)            = delete;  // copy ctor
    buffer& operator=(buffer const&) = delete;  // copy assign
    buffer(buffer&&)                 = default; // move ctor
    buffer& operator=(buffer&&)      = default; // move assign

public:
    buffer(std::uint32_t size, std::uint32_t stride) : m_size(size), m_stride(stride) {}

public:
    virtual std::span<std::byte> lock() = 0;

public:
    inline auto size() const { return m_size; }
    inline auto stride() const { return m_stride; }
    inline auto is_valid() const { return valid; }

protected:
    bool valid = false;

private:
    std::uint32_t m_size   = 0;
    std::uint32_t m_stride = 0;
};

} // namespace rdi

} // namespace ivd