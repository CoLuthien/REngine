

#pragma once

#include "test.h"
#include "core/core.hpp"
#include "core_object/core_object.hpp"

class T1 : public ivd::hobject
{
public:
    GENERATE_BODY();
    virtual ~T1() = default;
};

class Sample : public T1
{
public:
public:
public:
    struct this_type_tag;
    constexpr auto this_type_helper()
        -> decltype(refl ::detail ::this_type_writer<this_type_tag, decltype(this)>{}, void());
    using super     = this_type;
    using this_type = refl ::detail ::this_type_read<this_type_tag>;
    ;
    using pedigree_list = meta ::list ::push_front<super ::pedigree_list, this_type>;

public:
    template <std ::size_t>
    struct detail_field_reflection;
    template <std ::size_t>
    struct detail_function_reflection;

private:
    static consteval auto reflected_class() { return refl ::rclass ::make_class<this_type>(); };
    static consteval auto reflected_fields()
    {
        return refl ::as_initializer_list<refl ::gather_fields,
                                          this_type,
                                          refl ::field_counts<this_type>>::entry_point();
    };
    static consteval auto reflected_functions()
    {
        return refl ::as_initializer_list<refl ::gather_functions,
                                          this_type,
                                          refl ::func_counts<this_type>>::entry_point();
    };
    ;

public:
    this_type& operator=(this_type const&) = delete;
    this_type& operator=(this_type&&)      = delete;

public:
    template <typename C, typename... Args>
    friend C* new_object(ivd ::hobject* outer, Args... args);

public:
    inline static ivd ::hclass* static_class()
    {
        static constexpr auto fields   = reflected_fields();
        static constexpr auto funcs    = reflected_functions();
        static auto           instance = ivd ::hclass(reflected_class(),
                                            super ::static_class(),
                                            std ::span{fields.data(), fields.size()},
                                            std ::span{funcs.data(), funcs.size()});
        return &instance;
    };
    virtual ~Sample() = default;

public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b) { return a + b; }

private:
    REFLECT_FIELD(int const, x);
    REFLECT_FIELD(int const, y);
    REFLECT_FIELD(int const, z);
    REFLECT_FIELD(int, w);
};

class T3 : public Sample
{
    GENERATE_BODY();
};

T1* get_object();