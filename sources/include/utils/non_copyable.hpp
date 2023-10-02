
#pragma once

class non_copyable
{
public:
    non_copyable()          = default;
    virtual ~non_copyable() = default;

public:
    non_copyable(const non_copyable&)                = delete;
    non_copyable& operator=(const non_copyable&)     = delete;
    non_copyable(non_copyable&&) noexcept            = default;
    non_copyable& operator=(non_copyable&&) noexcept = default;
};