
#include "core/definitions.hpp"

namespace ivd
{
namespace math
{

template <typename T>
struct point4
{
public:
    constexpr point4(T in_x, T in_y, T in_z, T in_w);

public:
    T x{}, y{}, z{}, w{};
};

} // namespace math

} // namespace ivd