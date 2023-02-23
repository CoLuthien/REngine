
#pragma once



#define ENUM_ENTRY(NAME)                                                                 \
    struct detail_##NAME##_enum_tag;                                                     \
    static constexpr std::size_t NAME =                                                  \
        refl::detail::index<detail_##NAME##_enum_tag, detail_field_reflection>::value;   \
    template <class T>                                                                   \
    struct detail_field_reflection<detail_##NAME##_field_index, T>                       \
    {                                                                                    \
        using value_type                       = TYPES;                                  \
        static constexpr std::string_view name = #NAME;                                  \
        template <class U>                                                               \
        using pointer_type = value_type U::*;                                            \
        template <class U>                                                               \
        static constexpr value_type U::*pointer_value = &U::NAME;                        \
    };

#define ENUM_ENTRY_BITFIELD(NAME)                                                        \
    struct detail_##NAME##_enum_tag;                                                     \
    static constexpr std::size_t NAME =                                                  \
        1 << refl::detail::index<detail_##NAME##_enum_tag,                               \
                                 detail_field_reflection>::value;                        \
    template <class T>                                                                   \
    struct detail_field_reflection<detail_##NAME##_field_index, T>                       \
    {                                                                                    \
        using value_type                       = TYPES;                                  \
        static constexpr std::string_view name = #NAME;                                  \
        template <class U>                                                               \
        using pointer_type = value_type U::*;                                            \
        template <class U>                                                               \
        static constexpr value_type U::*pointer_value = &U::NAME;                        \
    };
