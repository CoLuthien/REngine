# Reflection Detail 

The first part of reflection is reflecting class variables and functions in compile time. 

First, we need to identify which entity will be reflected. Following code shows a simple example to reflect member functions and member variables. Each macro will deduce, possibly declare, a entity's property.

```cpp 
// in somewhere...
#define REFLECT_FIELD(TYPES, NAME) // ...
#define REFLECT_FUNCTION(NAME, .../*function arguments*/)//...

// in main.cpp

class Sample 
{
public:
    REFLECT_FUNCTION(add, int, int)
	int add(int a, int b){return a + b;}
public:
    REFLECT_FILED(int const, x);
}
```

Declaration or deduction of a single entity's property is relatively easy. But, using it from somewhere else is a problem. We need a data structure that is accessible at compile. 

Requirements for such data structure are 

1. Accessible through out same translation unit(in c++ view point).
2. Members must accessible at runtime.
3. An inserting operation must be done in class declaration

To meet these requirements, I use, compile time counter, frozen map.

For compile time counter, implementation as follows(tricky as hell...)

```c++
template <std::size_t, class, template <std::size_t, class> class>
struct index_impl // base case
{
    static constexpr std::size_t value = 0;
};

template <std::size_t I, class Tag, template <std::size_t, class> class Type>
requires requires
{
    Type<I, Tag>::name;
}
struct index_impl<I, Tag, Type> // iteration case 
{
    static constexpr std::size_t value = 1 + index_impl<I + 1, Tag, Type>::value;
};

template <class Tag, template <std::size_t, class> class Type>
struct index // entry point
{
    static constexpr std::size_t value = index_impl<0, Tag, Type>::value;
};

#define REFLECT_FIELD(TYPES, NAME)                                                       \
    TYPES NAME{};                                                                        \
    template <std::size_t, class>                                                        \
    struct detail_property_reflection;                                                   \
    static constexpr std::size_t detail_##NAME##_property_index =                        \
        refl::detail::index<struct detail_##NAME##_property_tag,                         \
                            detail_property_reflection>::value;                          \
    template <class T>                                                                   \
    struct detail_property_reflection<detail_##NAME##_property_index, T>                 \// tricky!!
    {                                                                                    \
        using value_type                       = TYPES;                                  \
        static constexpr std::string_view name = #NAME;                                  \
        template <class U>                                                               \
        using pointer_type = value_type U::*;                                            \
        template <class U>                                                               \
        static constexpr value_type U::*pointer_value = &U::NAME;                        \
    };

class Sample 
{
public:
    REFLECT_FIELD(int const, x); // 1st case => index = 0
    REFLECT_FIELD(int const, y); // 2nd case => index = 1
    REFLECT_FIELD(int const, z); // 3rd case => index = 2
};
```



Basically, it counts prior specialization of templates.  Details are left for future writing... 

TODO: Add non hobject type reflection like vector...



