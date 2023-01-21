
#pragma once

#include "reflection_concepts.hpp"
#include "reflection_utils.hpp"
#include "reflection_helper.hpp"

#include <type_traits>

namespace refl
{

class rfield_t
{
public:
    template <class Target, std::size_t I>
    static constexpr auto reflect_field()
    {
        using info_type = field_info_t<Target, I>;
        return rfield_t(static_cast<handle_t const*>(info_type::reflected_info()));
    }

public:
    template <class V>
    V get(void* obj) const
    {
        auto ptr = static_cast<field_iface_t<V> const*>(m_info);
        return ptr->get(obj);
    }
    template <class V>
    void set(void* obj, V value) const
    {
        auto ptr = static_cast<field_iface_t<V> const*>(m_info);
        return ptr->set(obj, value);
    }

private:
    struct handle_t;
    template <typename V>
    struct field_iface_t;

    template <class Target, std::size_t I>
    struct field_info_t;

private:
    constexpr rfield_t(handle_t const* handle) : m_info(handle) {}

private:
    handle_t const* m_info;
};

struct rfield_t::handle_t
{
    virtual ~handle_t() = default;
};

template <typename V>
struct rfield_t::field_iface_t : public rfield_t::handle_t
{
    virtual ~field_iface_t()                   = default;
    virtual V get(void* obj) const             = 0;
    virtual void set(void* obj, V value) const = 0;
};

template <class Target, std::size_t I>
struct rfield_t::field_info_t : public rfield_t::field_iface_t<field_value_t<Target, I>>
{
    using owner_type   = Target;
    using value_type   = field_value_t<Target, I>;
    using pointer_type = field_pointer_t<Target, I>;

    static constinit field_info_t const field_info;
    static constexpr pointer_type pointer = field_pointer_v<Target, I>;
    static constexpr auto name            = field_name_v<Target, I>;

    static constexpr auto reflected_info() { return &field_info; }
    // todo: make type flag that is for making antigen for GC

    virtual value_type get(void* obj) const
    {
        return reinterpret_cast<owner_type*>(obj)->*pointer;
    }
    virtual void set(void* obj, value_type value) const
    {
        if constexpr (std::is_const_v<value_type>)
        {
            return;
        }
        else
        {
            reinterpret_cast<owner_type*>(obj)->*pointer = value;
        }
    }
};

template <class Target, std::size_t I>
constinit rfield_t::field_info_t<Target, I> const
    rfield_t::field_info_t<Target, I>::field_info = {};

template <class Target, std::size_t Index>
struct gather_fields
{
    static constexpr auto instance = refl::rfield_t::reflect_field<Target, Index>();
    static constexpr std::string_view name = field_name_v<Target, Index>;
    static consteval std::pair<std::string_view, refl::rfield_t*> get_entry()
    {
        return std::make_pair(name, const_cast<rfield_t*>(&instance));
    }
};

} // namespace refl

#define REFLECT_FIELD(TYPES, NAME, ...)                                                  \
    TYPES NAME{};                                                                        \
    template <std::size_t, class>                                                        \
    struct detail_field_reflection;                                                      \
    struct detail_##NAME##_field_tag;                                                    \
    static constexpr std::size_t detail_##NAME##_field_index =                           \
        refl::detail::index<detail_##NAME##_field_tag, detail_field_reflection>::value;  \
    template <class T>                                                                   \
    struct detail_field_reflection<detail_##NAME##_field_index, T>                       \
    {                                                                                    \
        using value_type                       = TYPES;                                  \
        static constexpr std::string_view name = #NAME;                                  \
        template <class U>                                                               \
        using pointer_type = value_type U::*;                                            \
        template <class U>                                                               \
        static constexpr value_type U::*pointer_value = &U::NAME;                        \
    };
