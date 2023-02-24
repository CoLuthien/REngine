
#pragma once

#include "object.hpp"
#include "reflection/reflection.hpp"

#include <unordered_map>

namespace ivd
{

class DLLEXPORT hfield_t : public hobject_t
{
public:
    hfield_t(refl::rfield_t* field_info) : m_field(field_info) {}
    // todo: make type flag that is for making antigen for GC

    template <class T>
    T get(void* ptr) const
    {
        return m_field->get<T>(ptr);
    }

    template <class T>
    void set(void* ptr, T value) const
    {
        return m_field->set<T>(ptr, value);
    }

    refl::efield_type get_type() const noexcept { return m_field->get_type(); }

private:
    refl::rfield_t* m_field;
};

class DLLEXPORT hfunction_t : public hobject_t
{
public:
    hfunction_t(refl::rfunction_t* func_info) : m_func(func_info){};

    template <typename R, typename... Args>
    R invoke(void* obj, Args... args) const
    {
        return m_func->invoke<R>(obj, args...);
    }
    // implement invocation
private:
    refl::rfunction_t* m_func;
};

class DLLEXPORT hclass_t : public hobject_t
{
public:
    template <class Ps, class Fs>
    hclass_t(refl::rclass_t const* self_class,
             hclass_t* super_class,
             Ps const&& field_map,
             Fs const&& func_map)
        : m_self(self_class), m_super(super_class),
          m_fields(field_map.begin(), field_map.end()),
          m_functions(func_map.begin(), func_map.end())
    {
    }

public:
    hfunction_t const* DLLEXPORT find_func(std::string_view name);
    hfield_t const* DLLEXPORT find_field(std::string_view name);

private:
    hclass_t* m_super;
    refl::rclass_t const* m_self;
    std::unordered_map<std::string_view, hfunction_t> const m_functions;
    std::unordered_map<std::string_view, hfield_t> const m_fields;
};

} // namespace ivd
