
#include "core/definitions.hpp"
#include "point.hpp"
#include <concepts>

namespace ivd
{
namespace math
{

template <typename T>
struct vector2 : public point2<T>
{
public:
    constexpr vector2() = default;
    constexpr vector2(T in_x, T in_y);

public:
    using point2<T>::x;
    using point2<T>::y;

public:
};

template <typename T>
constexpr vector2<T>::vector2(T in_x, T in_y) : point2<T>(in_x, in_y)
{
}

template <typename T, std::floating_point U>
vector2<T>
operator*(vector2<T> const& v, U scale)
{
    T x = v.x * scale;
    T y = v.y * scale;
    return vector2<T>(x, y);
}

template <typename T, std::floating_point U>
vector2<T>
operator*(U scale, vector2<T> const& v)
{
    T x = v.x * scale;
    T y = v.y * scale;
    return vector2<T>(x, y);
}

} // namespace math
} // namespace ivd