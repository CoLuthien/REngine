
#pragma once

#include "object.hpp"
#include "reflection/reflection.hpp"

#include <unordered_map>

namespace ivd
{

class IVDAPI hfield : public hobject
{
public:
    hfield(refl::rfield* field_info) : m_field(field_info)
    {
        assert(m_field != nullptr);
    }

    template <class T>
    T get(void* ptr) const
    {
        return m_field->get<T>(ptr);
    }

    template <class T>
    void set(void* ptr, T value) const
    {
        m_field->set<T>(ptr, value);
    }

    refl::efield_type get_type() const noexcept
    {
        if (m_field)
        {
            return m_field->get_type();
        }
        
        return refl::efield_type::INVALID;
    }

private:
    refl::rfield* m_field;
};

class IVDAPI hfunction : public hobject
{
public:
    hfunction(refl::rfunction* func_info) : m_func(func_info){};

    template <typename R, typename... Args>
    R invoke(void* obj, Args... args) const
    {
        return m_func->invoke<R>(obj, args...);
    }
    // implement invocation
private:
    refl::rfunction* m_func;
};

class IVDAPI hclass : public hobject
{
public:
    using field_iter = std::unordered_map<std::string_view, hfield>::const_iterator;
    template <class Ps, class Fs>
    hclass(refl::rclass const&& self_class,
           hclass const* super_class,
           Ps const&& field_map,
           Fs const&& func_map)
        : m_self(self_class), m_super(super_class),
          m_fields(field_map.begin(), field_map.end()),
          m_functions(func_map.begin(), func_map.end())
    {
    }

public:
    hfunction const* find_func(std::string_view name) const;

    hfield const* find_field(std::string_view name) const;
    hclass const* get_super() const noexcept { return m_super; }
    auto const& get_fields() { return m_fields; }

private:
    hclass const* m_super;
    refl::rclass m_self;
    std::unordered_map<std::string_view, hfunction> const m_functions;
    std::unordered_map<std::string_view, hfield> const m_fields;
};

} // namespace ivd
