
#pragma once

#include "reflection/reflection.hpp"

#define GENERATE_BODY()                                                                  \
    REFLECT_CLASS();                                                                     \
                                                                                         \
public:                                                                                  \
    this_type& operator=(this_type const&) = delete;                                     \
    this_type& operator=(this_type&&)      = delete;                                     \
                                                                                         \
public:                                                                                  \
    inline static ivd::hclass_t* static_class()                                          \
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