
#pragma once

#include "reflection_utils.hpp"
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
class hclass;

} // namespace ivd

#define REFLECT_FUNCTIONS_INFO()                                                                   \
    static consteval auto reflected_functions()                                                    \
    {                                                                                              \
        return refl::as_initializer_list<refl::gather_functions,                                   \
                                         this_type,                                                \
                                         refl::func_counts<this_type>>::entry_point();             \
    }

#define REFLECT_FIELDS_INFO()                                                                      \
    static consteval auto reflected_fields()                                                       \
    {                                                                                              \
        return refl::as_initializer_list<refl::gather_fields,                                      \
                                         this_type,                                                \
                                         refl::field_counts<this_type>>::entry_point();            \
    }

#define REFLECT_CLASS_INFO()                                                                       \
    static consteval auto reflected_class()                                                        \
    {                                                                                              \
        return refl::rclass::make_class<this_type>();                                              \
    }

#define REFLECT_CLASS()                                                                            \
public:                                                                                            \
    DECLARE_TYPE();                                                                                \
    using pedigree_list = meta::list::push_front<super::pedigree_list, this_type>;                 \
                                                                                                   \
public:                                                                                            \
    template <std::size_t>                                                                         \
    struct detail_field_reflection;                                                                \
    template <std::size_t>                                                                         \
    struct detail_function_reflection;                                                             \
                                                                                                   \
private:                                                                                           \
    REFLECT_CLASS_INFO();                                                                          \
    REFLECT_FIELDS_INFO();                                                                         \
    REFLECT_FUNCTIONS_INFO();

/*************/
#define REFLECT_STRUCT()                                                                           \
public:                                                                                            \
    DECLARE_SINGLE_TYPE();                                                                         \
                                                                                                   \
public:                                                                                            \
    template <std::size_t>                                                                         \
    struct detail_field_reflection;                                                                \
    template <std::size_t>                                                                         \
    struct detail_function_reflection;                                                             \
                                                                                                   \
private:                                                                                           \
    REFLECT_CLASS_INFO();                                                                          \
    REFLECT_FIELDS_INFO();
