
#pragma once

#include "reflection_types.hpp"
#include "reflection_concepts.hpp"
#include "reflection_utils.hpp"
#include "reflection_helper.hpp"

#include <type_traits>

namespace refl
{

class rfield final
{
public:
    template <class Target, std::size_t I>
    static constexpr auto reflect_field()
    {
        using info_type = field_info_t<Target, I>;
        return rfield(static_cast<handle_t const*>(info_type::reflected_info()));
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

    inline efield_type get_type() const;

private:
    struct handle_t;
    template <typename V>
    struct field_iface_t;

    template <class Target, std::size_t I>
    struct field_info_t;

private:
    constexpr rfield(handle_t const* handle) : m_info(handle) {}

private:
    handle_t const* m_info;
};

struct rfield::handle_t
{
    virtual ~handle_t()                  = default;
    virtual efield_type get_type() const = 0;
};

efield_type
rfield::get_type() const
{
    return m_info->get_type();
}

template <typename V>
struct rfield::field_iface_t : public rfield::handle_t
{
    virtual ~field_iface_t()                   = default;
    virtual V get(void* obj) const             = 0;
    virtual void set(void* obj, V value) const = 0;
};

template <class Target, std::size_t I>
struct rfield::field_info_t final : public rfield::field_iface_t<field_value_t<Target, I>>
{
    using owner_type   = Target;
    using value_type   = field_value_t<Target, I>;
    using pointer_type = field_pointer_t<Target, I>;

    static constinit field_info_t const field_info;
    static constexpr pointer_type pointer = field_pointer_v<Target, I>;
    static constexpr auto name            = field_name_v<Target, I>;
    static constexpr auto field_type      = field_type_e<Target, I>();

    static consteval auto reflected_info() { return &field_info; }
    virtual efield_type get_type() const override { return field_type; }

    virtual value_type get(void* obj) const override
    {
        return reinterpret_cast<owner_type*>(obj)->*pointer;
    }
    virtual void set(void* obj, value_type value) const override
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
constinit rfield::field_info_t<Target, I> const
    rfield::field_info_t<Target, I>::field_info = {};

template <class Target, std::size_t Index>
struct gather_fields
{
    static constexpr auto instance         = refl::rfield::reflect_field<Target, Index>();
    static constexpr std::string_view name = field_name_v<Target, Index>;
    static consteval std::pair<std::string_view, refl::rfield*> get_entry()
    {
        return std::make_pair(name, const_cast<rfield*>(&instance));
    }
};

template <class Target>
struct gather_fields<Target, std::numeric_limits<std::size_t>::max()>
{
    static consteval std::pair<std::string_view, refl::rfield*> get_entry() { return {}; }
};

} // namespace refl

#define REFLECT_FIELD(TYPES, NAME, ...)                                                  \
    TYPES NAME{};                                                                        \
                                                                                         \
    struct detail_##NAME##_field_tag;                                                    \
    static constexpr std::size_t detail_##NAME##_field_index =                           \
        refl::detail::index<detail_##NAME##_field_tag, detail_field_reflection>::value;  \
    template <>                                                                          \
    struct detail_field_reflection<detail_##NAME##_field_index>                          \
    {                                                                                    \
        using value_type                       = TYPES;                                  \
        static constexpr std::string_view name = #NAME;                                  \
        template <class U>                                                               \
        using pointer_type = value_type U::*;                                            \
        template <class U>                                                               \
        static constexpr value_type U::*pointer_value = &U::NAME;                        \
    };
