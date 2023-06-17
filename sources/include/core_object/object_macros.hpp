
#pragma once

#include "reflection/reflection.hpp"
#include <span>

#define GENERATE_BODY()                                                                  \
    REFLECT_CLASS();                                                                     \
                                                                                         \
public:                                                                                  \
    this_type& operator=(this_type const&) = delete;                                     \
    this_type& operator=(this_type&&)      = delete;                                     \
                                                                                         \
private:                                                                                 \
    template <ivd::hobject_type T, typename... Args>                                     \
    friend T* new_object(ivd::hobject* outer, Args... args);                             \
                                                                                         \
    static void* operator new(std::size_t count)                                         \
    {                                                                                    \
        return ::operator new(count);                                                    \
    }                                                                                    \
                                                                                         \
public:                                                                                  \
    inline static ivd::hclass* static_class()                                            \
    {                                                                                    \
        static constexpr auto fields = reflected_fields();                               \
        static constexpr auto funcs  = reflected_functions();                            \
                                                                                         \
        static auto instance = ivd::hclass(reflected_class(),                            \
                                           super::static_class(),                        \
                                           std::span{fields.data(), fields.size()},      \
                                           std::span{funcs.data(), funcs.size()});       \
        return &instance;                                                                \
    }

#define GENERATE_HOBJECT_BODY()                                                          \
public:                                                                                  \
    using super         = std::nullptr_t;                                                \
    using this_type     = hobject;                                                       \
    using pedigree_list = meta::typelist<super>;                                         \
    static ivd::hclass* static_class();                                                  \
                                                                                         \
private:                                                                                 \
    REFLECT_CLASS_INFO();                                                                \
    REFLECT_FIELDS_INFO();                                                               \
    REFLECT_FUNCTIONS_INFO();                                                            \
                                                                                         \
public:                                                                                  \
    template <std::size_t>                                                               \
    struct detail_field_reflection;                                                      \
    template <std::size_t>                                                               \
    struct detail_function_reflection;                                                   \
                                                                                         \
public:                                                                                  \
    hobject& operator=(hobject const&) = delete;                                         \
    hobject(hobject const&)            = delete;                                         \
    hobject& operator=(hobject&&)      = delete;                                         \
    hobject(hobject&&)                 = delete;