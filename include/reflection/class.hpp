
#pragma once

#include "detail.hpp"
#include "object.hpp"
#include "property.hpp"
#include "function.hpp"
#include "type_helper.hpp"

#include "frozen/unordered_map.h"
#include "frozen/bits/elsa_std.h"

#include <cstddef>
#include <string_view>

namespace refl
{

template <class Target>
concept HasReflectedMember =
    requires {
        typename Target::template detail_function_reflection<0, Target>;
        typename Target::template detail_property_reflection<0, Target>;
    };

template <class T>
struct type_info
{
};

class refl_class_t
{
public:
    constexpr refl_class_t(refl_class_t const&) = default;
    void* operator new(std::size_t size)        = delete;

    constexpr auto get_function(std::string_view const name) const
    {
        return m_ptr->get_function(name);
    }

    constexpr auto get_property(std::string_view const name) const
    {
        return m_ptr->get_property(name);
    }

    template <class Target>
    static constexpr auto make_reflection()
    {
        if constexpr (HasReflectedMember<Target>)
        {
            return refl_class_t{type_info<Target>{}};
        }
        else
        {
            return refl_class_t{};
        }
    }

private:
    template <class Target>
    constexpr refl_class_t(type_info<Target>)
    {
        using object_type = member_info_t<Target>;

        m_ptr = static_cast<handle_t const*>(object_type::get_instance());
    }
    constexpr refl_class_t() = default;

private:
    struct handle_t
    {
        using func_pair = std::pair<std::string_view, refl_func_t>;
        using prop_pair = std::pair<std::string_view, refl_prop_t>;
        virtual refl_func_t get_function(std::string_view name) const noexcept = 0;
        virtual refl_prop_t get_property(std::string_view name) const noexcept = 0;
    };

    template <class Target>
    struct member_info_t;

private:
    handle_t const* m_ptr;
};

template <class Target>
struct refl_class_t::member_info_t : public refl_class_t::handle_t
{
    static constinit const member_info_t instance;
    virtual refl_func_t get_function(std::string_view name) const noexcept override
    {
        return m_funcs.at(name);
    }
    virtual refl_prop_t get_property(std::string_view name) const noexcept override
    {
        return m_props.at(name);
    }
    static consteval auto get_instance() { return &instance; }

    static constexpr auto m_funcs =
        to_frozen_map<function_info, Target, count_functions<Target>>::make_map();
    static constexpr auto m_props =
        to_frozen_map<property_info, Target, count_properties<Target>>::make_map();
    static constexpr auto num_funcs = m_funcs.size();
    static constexpr auto num_props = m_props.size();
};

template <class Target>
constinit const refl_class_t::member_info_t<Target>
    refl_class_t::member_info_t<Target>::instance = {};

#define REFLECT_CLASS()                                                                  \
    DECLARE_TYPE();                                                                      \
                                                                                         \
public:                                                                                  \
    static refl::refl_class_t* reflected_class()                                         \
    {                                                                                    \
        static constexpr auto type = refl::refl_class_t::make_reflection<this_type>();   \
        return const_cast<refl::refl_class_t*>(&type);                                   \
    }

} // namespace refl
