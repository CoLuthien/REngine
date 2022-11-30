
#pragma once

#include "Detail.hpp"
#include "Concepts.hpp"
#include "type_helper.hpp"
#include "types.hpp"

#include <cstddef>
#include <string_view>

namespace refl
{

class RField
{
private:
    template <class Target, std::size_t Index>
        requires HasReflectedField<Target>
    constexpr RField(dummy_t<Target, Index>) : m_name(field_name_v<Target, Index>)
    {
        using object_type = FieldInformation<Target, Index>;
        m_native          = static_cast<Handle const*>(object_type::get_instance());
    }
    template <class Target, std::size_t Index>
    static constexpr std::string_view get_name()
    {
        return field_name_v<Target, Index>;
    }
    auto get_name() { return m_name; }

public:
    template <class Target, std::size_t Index>
    static constexpr auto make_info()
    {
        return std::make_pair(get_name<Target, Index>(),
                              RField(dummy_t<Target, Index>{}));
    }

public:
    template <typename T>
    T get(void* object) const
    {
        auto iface = static_cast<FieldInterface<T> const*>(m_native);
        return iface->get(object);
    }
    template <typename T>
    void set(void* object, T value) const
    {
        auto iface = static_cast<FieldInterface<T> const*>(m_native);
        return iface->set(object, value);
    }

private:
    struct Handle
    {
        virtual ~Handle() = default;
    };

    template <typename T>
    struct FieldInterface : public Handle
    {
        virtual ~FieldInterface()         = default;
        virtual T get(void* object) const = 0;
        virtual void set(void* object, T value) const;
    };
    template <class Target, std::size_t Index>
    struct FieldInformation;

private:
    Handle const* m_native;
    std::string_view const m_name;
};

template <class Target, std::size_t Index>
struct RField::FieldInformation
    : public RField::FieldInterface<field_value_t<Target, Index>> // globally unique
{
    using ptr_type   = field_ptr_t<Target, Index>;
    using value_type = field_value_t<Target, Index>;
    using owner_type = Target;

    static constinit const FieldInformation instance;
    static constexpr FieldInformation const* get_instance() { return &instance; }
    static constexpr ptr_type ptr          = prop_ptr_v<Target, Index>;  // just an offset
    static constexpr std::string_view name = field_name_v<Target, Index>; // name

    constexpr FieldInformation() = default;

    virtual value_type get(void* object) const override
    {
        return static_cast<owner_type*>(object)->*ptr;
    }
    virtual void set(void* object, value_type value) const override
    {
        if constexpr (std::is_const_v<value_type>)
        {
            return;
        }
        else
        {
            static_cast<owner_type*>(object)->*ptr = value;
        }
    }
};

template <class Target, std::size_t Index>
constinit const RField::FieldInformation<Target, Index>
    RField::FieldInformation<Target, Index>::instance = {};

template <class Target, std::size_t Index>
struct property_info
{
    static consteval std::pair<std::string_view, refl::RField> get_entry()
    {
        return refl::RField::make_info<Target, Index>();
    }
};

} // namespace refl

#define REFLECT_MEMBER(TYPES, NAME, ...)                                                 \
    TYPES NAME{};                                                                        \
    template <size_t, class>                                                             \
    struct detail_property_reflection;                                                   \
    static constexpr std::size_t detail_##NAME##_property_index =                        \
        refl::detail::index<struct detail_##NAME##_property_tag,                         \
                            detail_property_reflection>::value;                          \
    template <class T>                                                                   \
    struct detail_property_reflection<detail_##NAME##_property_index, T>                 \
    {                                                                                    \
        using type                             = TYPES;                                  \
        static constexpr std::string_view name = #NAME;                                  \
        template <class U>                                                               \
        using ptr_type = type U::*;                                                      \
        template <class U>                                                               \
        static constexpr type U::*offset_v = &U::NAME;                                   \
    };
