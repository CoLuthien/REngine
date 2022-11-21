
#pragma once

#include "property.hpp"
#include "function.hpp"
#include "type_helper.hpp"

#include "frozen/unordered_map.h"
#include "frozen/bits/elsa_std.h"

#include <cstddef>
#include <string_view>

namespace refl
{

template <template <class, std::size_t> class Info, class Target, std::size_t Index>
struct to_frozen_map
{
    static constexpr auto value = Info<Target, Index - 1>::get_entry();

    static consteval auto make_map()
    {
        return to_frozen_map<Info, Target, Index - 1>::recurse(value);
    }

    template <typename T, typename... Args>
    static consteval auto recurse(T v, Args... args)
    {
        return to_frozen_map<Info, Target, Index - 1>::recurse(value, v, args...);
    }
};

template <template <class, std::size_t> class Info, class Target>
struct to_frozen_map<Info, Target, 0>
{
    template <typename... Args>
    static consteval auto recurse(Args... args)
    {
        return frozen::make_unordered_map({args...});
    }
};

template <class T>
struct type_info
{
};

class refl_class_t
{
public:
    refl_class_t(refl_class_t const&) = default;

    auto get_function(std::string_view const name) const
    {
        return m_ptr->get_function(name);
    }
    auto get_property(std::string_view const name) const
    {
        return m_ptr->get_property(name);
    }

    template <class Target>
    static consteval auto make_reflection()
    {
        return refl_class_t{type_info<Target>{}};
    }

private:
    template <class Target>
    consteval refl_class_t(type_info<Target>)
        : n_funcs(refl_class_info_t<Target>::num_funcs),
          n_props(refl_class_info_t<Target>::num_props)
    {
        using object_type = refl_class_info_t<Target>;

        m_ptr = static_cast<handle_t const*>(object_type::get_instance());
    }

private:
    struct handle_t
    {
        using func_pair = std::pair<std::string_view, refl_func_t>;
        using prop_pair = std::pair<std::string_view, refl_prop_t>;
        virtual func_pair const* get_function(std::string_view name) const noexcept = 0;
        virtual prop_pair const* get_property(std::string_view name) const noexcept = 0;
    };

    template <class Target>
    struct refl_class_info_t : public handle_t
    {
        static constinit const refl_class_info_t instance;
        virtual func_pair const* get_function(
            std::string_view name) const noexcept override
        {
            return m_funcs.find(name);
        }
        virtual prop_pair const* get_property(
            std::string_view name) const noexcept override
        {
            return m_props.find(name);
        }
        static consteval auto get_instance() { return &instance; }

        static constexpr auto m_funcs =
            to_frozen_map<function_info, Target, count_functions<Target>>::make_map();
        static constexpr auto m_props =
            to_frozen_map<property_info, Target, count_properties<Target>>::make_map();
        static constexpr auto num_funcs = m_funcs.size();
        static constexpr auto num_props = m_props.size();
    };

private:
    handle_t const* m_ptr;
    std::size_t const n_funcs;
    std::size_t const n_props;
};
template <class Target>
constinit const refl_class_t::refl_class_info_t<Target>
    refl_class_t::refl_class_info_t<Target>::instance = {};

#define REGISTER_CLASS(NAME)

} // namespace refl
