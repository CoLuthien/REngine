
#pragma once

#include "HAL/attributes.hpp"

namespace ivd
{
class DLLEXPORT non_copyable
{
public:
    virtual ~non_copyable() = default;

public:
    non_copyable(const non_copyable&)                = delete;
    non_copyable(non_copyable&&) noexcept            = default;
    non_copyable& operator=(const non_copyable&)     = delete;
    non_copyable& operator=(non_copyable&&) noexcept = default;
};
} // namespace ivd