
#pragma once

#include <stdint.h>
#include <cstddef>

namespace refl
{
using index_t = int32_t;
class refl_class_t;

class refl_object_t
{
public:
    using this_type = refl_object_t;
    refl_object_t() = default;

private:
    index_t m_index;
    class refl_class_t* m_class;
    class refl_object_t* m_owner;
};

class g_func_t
{

};

template <class T, typename... Args>
T*
make_reflected(Args... args)
{
    auto* ptr = new T{std::forward<Args>(args)...};
    return ptr;
}

} // namespace refl
