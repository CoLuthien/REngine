
#pragma once

#include "core_export.hpp"
#include "basics.hpp"

namespace ivd
{
namespace math
{

template <std::floating_point T>
struct rotator
{
public:
    rotator() = default;

public:
    T roll, pitch, yaw;
};

} // namespace math

} // namespace ivd