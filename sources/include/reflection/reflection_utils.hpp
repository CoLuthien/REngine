
#pragma once

#include <cstddef>
#include <type_traits>

namespace refl
{

// compile time index
namespace detail
{
template <std::size_t, class, template <std::size_t, class> class>
struct index_impl
{
    static constexpr std::size_t value = 0;
};

template <std::size_t I, class Tag, template <std::size_t, class> class Type>
    requires requires { Type<I, Tag>::name; }
struct index_impl<I, Tag, Type>
{
    static constexpr std::size_t value = 1 + index_impl<I + 1, Tag, Type>::value;
};

template <class Tag, template <std::size_t, class> class Type>
struct index
{
    static constexpr std::size_t value = index_impl<0, Tag, Type>::value;
};

} // namespace detail

// compile time this_type
namespace detail
{
template <typename Tag>
struct this_type_reader
{
    friend auto this_type(this_type_reader<Tag>);
};

template <typename Tag, typename ThisType>
struct this_type_writer
{
    // inline friend function declaration to exploit ThisType from template x(
    friend auto this_type(this_type_reader<Tag>) { return ThisType{}; }
};

template <typename Tag>
using this_type_read =
    std::remove_pointer_t<decltype(this_type(std::declval<this_type_reader<Tag>>()))>;

} // namespace detail

} // namespace refl

#define DECLARE_TYPE()                                                                   \
public:                                                                                  \
    struct this_type_tag;                                                                \
    constexpr auto this_type_helper()                                                    \
        ->decltype(refl::detail::this_type_writer<this_type_tag, decltype(this)>{},      \
                   void());                                                              \
    using super     = this_type;                                                         \
    using this_type = refl::detail::this_type_read<this_type_tag>;
