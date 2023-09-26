
#pragma once

#include "rdi_export.hpp"
#include "rdi/rdi_constants.hpp"

#include <memory>

#include <array>

namespace ivd
{
namespace rdi
{

class RDI_API rdi_frame
{
public:
    rdi_frame() = default;

public:
    virtual void begin() = 0;
    virtual void end()   = 0;
};

class RDI_API rdi_frame_manager
{
public:
    virtual rdi_frame* get_next_frame() = 0;

private:
    std::array<std::unique_ptr<rdi_frame>, concurrent_frame_count> m_frames;
};

} // namespace rdi

} // namespace ivd