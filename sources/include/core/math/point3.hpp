
#include "core/definitions.hpp"

namespace ivd
{
namespace math
{

template <typename T>
struct point3
{
public:
    constexpr point3() = default;
    constexpr point3(T value) : x(value), y(value), z(value) {}
    constexpr point3(T in_x, T in_y, T in_z) : x(in_x), y(in_y), z(in_z) {}

public:
    T x{}, y{}, z{};
};

} // namespace math

} // namespace ivd