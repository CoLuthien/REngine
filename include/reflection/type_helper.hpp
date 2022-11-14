
#pragma once

#include <type_traits>

namespace refl
{
namespace type_helper
{
template <typename T>
struct this_type_reader
{
    friend auto this_type(this_type_reader<T>);
};

template <typename T, typename U>
struct this_type_writer
{
    friend auto this_type(this_type_reader<T>) { return U{}; }
};

inline void this_type();

template <typename T>
using this_type_read = std::remove_pointer_t<decltype(this_type(this_type_reader<T>{}))>;

} // namespace type_helper

} // namespace refl

#define DECLARE_TYPE()                                                                   \
public:                                                                                  \
    constexpr auto this_type_helper()                                                    \
        ->decltype(refl::type_helper::this_type_writer<struct this_type_tag,             \
                                                       decltype(this)>{},                \
                   void());                                                              \
    using super     = this_type;                                                         \
    using this_type = refl::type_helper::this_type_read<struct this_type_tag>;
