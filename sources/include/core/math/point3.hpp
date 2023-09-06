
#include "core_export.hpp"
#include "core_object.hpp"

namespace ivd
{
namespace math
{

template <typename T>
struct point3
{
    GENERATE_STRUCT();

public:
    constexpr point3() = default;
    constexpr point3(T value) : x(value), y(value), z(value) {}
    constexpr point3(T in_x, T in_y, T in_z) : x(in_x), y(in_y), z(in_z) {}

public:
    REFLECT_FIELD(T, x);
    REFLECT_FIELD(T, y);
    REFLECT_FIELD(T, z);
};

} // namespace math

} // namespace ivd