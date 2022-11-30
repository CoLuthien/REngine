
#pragma once

#include <stdint.h>
#include <cstddef>

namespace refl
{
class RClass;
class RField;
class RFunction;

} // namespace refl

namespace ge
{
using index_t = int32_t;

class GObject
{
public:
    using this_type = GObject;
    GObject()       = default;

private:
    index_t m_index;
    class GClass* m_owner;
};

template <class T, typename... Args>
T*
make_reflected(Args... args)
{
    auto* ptr = new T{std::forward<Args>(args)...};
    return ptr;
}

} // namespace ge
