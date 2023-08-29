
#pragma once

#include "object.hpp"
#include "reflection/reflection.hpp"
#include "core_object/definitions.hpp"

#include <unordered_map>
#include <span>

namespace ivd
{

using hfield    = refl::rfield;
using hfunction = refl::rfunction;
class COREOBJECT_API hstruct : public hobject
{
public:
    hstruct(refl::rclass&&                                              self_class,
            std::span<std::pair<std::string_view, refl::rfield*> const> field_span)
        : m_self(self_class), m_fields(field_span.begin(), field_span.end())
    {
    }

private:
    refl::rclass                                        m_self;
    std::unordered_map<std::string_view, hfield*> const m_fields;
};

class COREOBJECT_API hclass : public hobject
{
public:
    hclass(refl::rclass&&                                                 self_class,
           hclass* const                                                  super_class,
           std::span<std::pair<std::string_view, refl::rfield*> const>    field_map,
           std::span<std::pair<std::string_view, refl::rfunction*> const> func_map)
        : m_super(super_class), m_self(self_class), m_fields(field_map.begin(), field_map.end()),
          m_functions(func_map.begin(), func_map.end())
    {
    }

public:
    hfunction const* find_func(std::string_view name) const;
    hfield const*    find_field(std::string_view name) const;
    hfunction*       find_func(std::string_view name);
    hfield*          find_field(std::string_view name);

    hclass const* get_super() const noexcept { return m_super; }
    auto const&   get_fields() { return m_fields; }

private:
    hclass* const                                          m_super;
    refl::rclass                                           m_self;
    std::unordered_map<std::string_view, hfield*> const    m_fields;
    std::unordered_map<std::string_view, hfunction*> const m_functions;
};

} // namespace ivd
