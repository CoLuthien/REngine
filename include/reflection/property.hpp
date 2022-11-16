
#pragma once

#include "detail.hpp"
#include "type_helper.hpp"

#include <cstddef>
#include <string_view>

namespace refl
{

class refl_prop_t
{
public:
    template <class Target, std::size_t Index>
    consteval refl_prop_t(dummy_t<Target, Index>) : m_name(prop_name_v<Target, Index>)
    {
        using object_type = prop_object_t<Target, Index>;
        m_ptr             = static_cast<handle_t const*>(object_type::get_instance());
    }

public:
    consteval std::pair<std::string_view, refl_prop_t> make_info()
    {
        return std::make_pair(get_name(), *this);
    }

public:
    consteval std::string_view const get_name() const { return m_name; }
    template <typename T>
    T get(void* object) const
    {
        auto iface = static_cast<interface_t<T> const*>(m_ptr);
        return iface->get(object);
    }
    template <typename T>
    void set(void* object, T value) const
    {
        auto iface = static_cast<interface_t<T> const*>(m_ptr);
        return iface->set(object, value);
    }

private:
    struct handle_t
    {
    };

    template <typename T>
    struct interface_t : public handle_t
    {
        virtual T get(void* object) const             = 0;
        virtual void set(void* object, T value) const = 0;
    };

    template <class Target, std::size_t Index>
    struct prop_object_t
        : public interface_t<typename refl_prop_info<Target, Index>::type> // unique for
                                                                           // all data
    {
        using refl_info  = refl_prop_info<Target, Index>;
        using type       = typename refl_info::template ptr_type<Target>;
        using value_type = typename refl_info::type;
        using owner_type = Target;

        constexpr prop_object_t() = default;

        virtual value_type get(void* object) const override
        {
            return static_cast<owner_type*>(object)->*ptr;
        }
        virtual void set(void* object, value_type value) const override
        {
            static_cast<owner_type*>(object)->*ptr = value;
        }

        static constexpr prop_object_t const* get_instance() { return &instance; }
        static constexpr type ptr = prop_ptr_v<Target, Index>; // just an offset
        static constexpr std::string_view name = prop_name_v<Target, Index>; // name
        static constinit const prop_object_t instance;
    };

private:
    handle_t const* m_ptr;
    std::string_view const m_name;
};

template <class Target, std::size_t Index>
constinit const refl_prop_t::prop_object_t<Target, Index>
    refl_prop_t::prop_object_t<Target, Index>::instance = {};

template <class Target, std::size_t Index>
struct property_info
{
    static consteval std::pair<std::string_view, refl::refl_prop_t> get_entry()
    {
        return refl::refl_prop_t(refl::dummy_t<Target, Index>()).make_info();
    }
};

} // namespace refl

#define REFLECT_MEMBER(NAME, ...)                                                        \
    __VA_ARGS__ NAME{};                                                                  \
    template <size_t, class>                                                             \
    struct detail_property_reflection;                                                   \
    static constexpr std::size_t detail_##NAME##_property_index =                        \
        refl::detail::index<struct detail_##NAME##_property_tag,                         \
                            detail_property_reflection>::value;                          \
    template <class T>                                                                   \
    struct detail_property_reflection<detail_##NAME##_property_index, T>                 \
    {                                                                                    \
        using type                             = __VA_ARGS__;                            \
        static constexpr std::string_view name = #NAME;                                  \
        template <class U>                                                               \
        using ptr_type = type U::*;                                                      \
        template <class U>                                                               \
        static constexpr type U::*offset_v = &U::NAME;                                   \
    };
