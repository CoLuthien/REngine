
#pragma once

#include <stdint.h>
#include <unordered_map>
#include <string_view>
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
class GObject;

class GObjectContainer
{
};

class GObject
{
public:
    using this_type = GObject;

    class GFunction* find_function(std::string_view const name);

private:
    index_t m_index;
    class GClass* m_type;
};

template <class T, typename... Args>
T*
make_reflected(Args... args)
{
    auto* ptr = new T{std::forward<Args>(args)...};
    return ptr;
}

} // namespace ge
