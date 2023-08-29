
#include "class.hpp"
#include <string_view>
#include <iostream>

namespace ivd
{

hfunction const*
hclass::find_func(std::string_view name) const
{
    if (m_functions.contains(name))
    {
        return m_functions.at(name);
    }
    return m_super == nullptr ? nullptr : m_super->find_func(name);
}
refl::rfield const*
hclass::find_field(std::string_view name) const
{
    if (m_fields.contains(name))
    {
        return m_fields.at(name);
    }
    return nullptr;
}

hfunction*
hclass::find_func(std::string_view name)
{
    if (m_functions.contains(name))
    {
        return m_functions.at(name);
    }
    return m_super == nullptr ? nullptr : m_super->find_func(name);
}
refl::rfield*
hclass::find_field(std::string_view name)
{
    if (m_fields.contains(name))
    {
        return m_fields.at(name);
    }
    return nullptr;
}

} // namespace ivd
