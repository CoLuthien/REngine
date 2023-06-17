
#include "class.hpp"
#include <string_view>
#include <iostream>

namespace ivd
{

COREOBJECT_API hfunction const*
hclass::find_func(std::string_view name) const
{
    auto iter = m_functions.find(name);
    if (iter == m_functions.end())
    {
        return m_super == nullptr ? nullptr : m_super->find_func(name);
    }

    return &(iter->second);
}
COREOBJECT_API hfield const*
hclass::find_field(std::string_view name) const
{
    auto iter = m_fields.find(name);
    if (iter == m_fields.end())
    {
        return m_super == nullptr ? nullptr : m_super->find_field(name);
    }

    return &(iter->second);
}

} // namespace ivd
