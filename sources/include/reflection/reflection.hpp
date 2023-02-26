
#pragma once

#include "reflection_types.hpp"
#include "reflection_concepts.hpp"
#include "reflection_helper.hpp"
#include "reflection_generator.hpp"

#include "field_reflection.hpp"
#include "function_reflection.hpp"
#include "class_reflection.hpp"

#include "meta/type_list.hpp"
#include <frozen/unordered_map.h>

namespace ivd
{
class hclass_t;

} // namespace ivd

#define REFLECT_FUNCTIONS_INFO()                                                         \
    static consteval auto reflected_functions()                                          \
    {                                                                                    \
        return refl::to_array<refl::gather_functions,                                    \
                              this_type,                                                 \
                              refl::func_counts<this_type>>::entry_point();              \
    }

#define REFLECT_FIELDS_INFO()                                                            \
    static consteval auto reflected_fields()                                             \
    {                                                                                    \
        return refl::reflect_all_t<this_type::pedigree_list,                             \
                                   refl::gather_fields,                                  \
                                   refl::field_counter>::entry();                        \
    }

#define REFLECT_CLASS_INFO()                                                             \
    static consteval auto reflected_class()                                              \
    {                                                                                    \
        return refl::rclass_t::make_class<this_type>();                                  \
    }

#define REFLECT_CLASS()                                                                  \
    DECLARE_TYPE();                                                                      \
    using pedigree_list = meta::list::push_front<super::pedigree_list, this_type>;       \
    virtual ivd::hclass_t const* get_class() const override                              \
    {                                                                                    \
        return this_type::static_class();                                                \
    }                                                                                    \
                                                                                         \
private:                                                                                 \
    REFLECT_CLASS_INFO();                                                                \
    REFLECT_FIELDS_INFO();                                                               \
    REFLECT_FUNCTIONS_INFO();

#define GENERATE_BODY()                                                                  \
    REFLECT_CLASS();                                                                     \
                                                                                         \
public:                                                                                  \
    template <std::size_t, class>                                                        \
    struct detail_field_reflection;                                                      \
    template <std::size_t, class>                                                        \
    struct detail_function_reflection;                                                   \
                                                                                         \
public:                                                                                  \
    this_type& operator=(this_type const&) = delete;                                     \
    this_type& operator=(this_type&&)      = delete;                                     \
                                                                                         \
public:                                                                                  \
    static ivd::hclass_t const* static_class()                                           \
    {                                                                                    \
        static auto instance = ivd::hclass_t(reflected_class(),                          \
                                             super::static_class(),                      \
                                             reflected_fields(),                         \
                                             reflected_functions());                     \
        return &instance;                                                                \
    }

#define GENERATE_HOBJECT_BODY()                                                          \
public:                                                                                  \
    using super         = std::nullptr_t;                                                \
    using this_type     = hobject_t;                                                     \
    using pedigree_list = meta::typelist<super>;                                         \
    static ivd::hclass_t* static_class();                                                \
                                                                                         \
private:                                                                                 \
    REFLECT_CLASS_INFO();                                                                \
    REFLECT_FIELDS_INFO();                                                               \
    REFLECT_FUNCTIONS_INFO();                                                            \
                                                                                         \
public:                                                                                  \
    template <std::size_t, class>                                                        \
    struct detail_field_reflection;                                                      \
    template <std::size_t, class>                                                        \
    struct detail_function_reflection;                                                   \
                                                                                         \
public:                                                                                  \
    hobject_t& operator=(hobject_t const&) = delete;                                     \
    hobject_t(hobject_t const&)            = delete;                                     \
    hobject_t& operator=(hobject_t&&)      = delete;                                     \
    hobject_t(hobject_t&&)                 = delete;
