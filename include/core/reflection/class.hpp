
#pragma once

#include "Detail.hpp"
#include "Field.hpp"
#include "Function.hpp"
#include "Concepts.hpp"
#include "type_helper.hpp"

#include <cstddef>
#include <string_view>

namespace refl
{

template <class T>
struct type_info
{
};

class RClass
{
public:
    constexpr RClass(RClass const&)      = delete;
    void* operator new(std::size_t size) = delete;

    constexpr auto get_function(std::string_view const name) const
    {
        return m_native->get_function(name);
    }

    constexpr auto get_property(std::string_view const name) const
    {
        return m_native->get_property(name);
    }

    template <class Target>
    static constexpr auto make_reflection()
    {
        return RClass{type_info<Target>{}};
    }

private:
    template <class Target>
    constexpr RClass(type_info<Target>)
    {
        using object_type = MemberInfo<Target>;

        m_native = static_cast<Handle const*>(object_type::get_instance());
    }
    constexpr RClass() = default;

private:
    struct Handle
    {
        virtual RFunction get_function(std::string_view name) const noexcept = 0;
        virtual RField get_property(std::string_view name) const noexcept    = 0;
    };

    template <class Target>
    struct MemberInfo;

private:
    Handle const* m_native;
};

template <class Target>
struct RClass::MemberInfo : public RClass::Handle
{
    virtual RFunction get_function(std::string_view name) const noexcept override
    {
        return m_funcs.at(name);
    }
    virtual RField get_property(std::string_view name) const noexcept override
    {
        return m_props.at(name);
    }
    static consteval auto get_instance() { return &instance; }

    static constinit const MemberInfo instance;
    static constexpr auto m_funcs =
        to_frozen_map<function_info, Target, function_counts<Target>>::make_map();
    static constexpr auto m_props =
        to_frozen_map<property_info, Target, field_counts<Target>>::make_map();
};

template <class Target>
constinit const RClass::MemberInfo<Target> RClass::MemberInfo<Target>::instance = {};

#define REFLECT_CLASS()                                                                  \
    DECLARE_TYPE();                                                                      \
                                                                                         \
public:                                                                                  \
    static refl::RClass* reflected_class()                                               \
    {                                                                                    \
        static constexpr auto type = refl::RClass::make_reflection<this_type>();         \
        return const_cast<refl::RClass*>(&type);                                         \
    }

} // namespace refl
