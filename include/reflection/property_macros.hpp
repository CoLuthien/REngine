
#pragma once

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

#define REFELCT_MEMBER_DEFAULT(NAME, TYPE) REFLECT_MEMBER(NAME, TYPE)
#define REFLECT_1ARGS(A, B, C) REFELCT_MEMBER_DEFAULT(A, B)
#define REFLECT_2ARGS(A, B, C, D) REFELCT_MEMBER_DEFAULT(A, B)
#define REFLECT_3ARGS(A, B, C, D, E) REFELCT_MEMBER_DEFAULT(A, B)

#define GET_6TH(A, B, C, D, E, F, ...) F

#define REFLECTION_CHOOSE(...)                                                           \
    GET_6TH(__VA_ARGS__,                                                                 \
            REFLECT_3ARGS,                                                               \
            REFLECT_2ARGS,                                                               \
            REFLECT_1ARGS,                                                               \
            REFELCT_MEMBER_DEFAULT, )

#define REFLECT_MEMBER2(...) REFLECTION_CHOOSE(__VA_ARGS__)(__VA_ARGS__)