
#include "class.hpp"
#include <string_view>
#include <iostream>

namespace ivd
{

hfunction_t const* DLLEXPORT
hclass_t::find_func(std::string_view name) const
{
    auto iter = m_functions.find(name);
    if (iter == m_functions.end())
    {
        return m_super == nullptr ? nullptr : m_super->find_func(name);
    }

    return &(iter->second);
}
hfield_t const* DLLEXPORT
hclass_t::find_field(std::string_view name) const
{
    auto const iter = m_fields.find(name);
    return iter == m_fields.end() ? nullptr : &(iter->second);
}

} // namespace ivd
