
#pragma once

#include "type_helper.hpp"

class GType
{
public:
};

template <typename C, typename T, std::string_view Name>
struct GPropertyStaticInfo
{
    using OnwerType = C;
    using MyType = T;
    static constexpr std::string_view m_name = Name;
    constexpr GPropertyStaticInfo();
};

template <typename T, std::string_view Name>
class GFunctionInfoStatic : public GType
{
public:
    consteval GFunctionInfoStatic()
    {
    }
};