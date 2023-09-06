
#include "core/definitions.hpp"
#include "point.hpp"
#include "basics.hpp"
#include "meta/concepts.hpp"

#include <concepts>

namespace ivd
{
namespace math
{

template <meta::arithmetic_type T>
struct vector2 : public point2<T>
{
public:
    constexpr vector2() = default;
    constexpr vector2(T in_x, T in_y);

public:
    T          squred_norm() const { return x * x + y * y; }
    T          norm() const { return ops::sqrt(squred_norm()); }
    bool       normalize(T const eps = epsilon<T>);
    vector2<T> normalized(T const eps = epsilon<T>) const;

public:
    using point2<T>::x;
    using point2<T>::y;
};

template <meta::arithmetic_type T>
constexpr vector2<T>::vector2(T in_x, T in_y) : point2<T>(in_x, in_y)
{
}

template <meta::arithmetic_type T, meta::arithmetic_type U>
inline vector2<T>
operator/(vector2<T> const& v, U scale)
{
    T x = v.x / static_cast<T>(scale);
    T y = v.y / static_cast<T>(scale);
    return vector2<T>(x, y);
}

template <meta::arithmetic_type T, meta::arithmetic_type U>
inline vector2<T>
operator*(vector2<T> const& v, U scale)
{
    T x = v.x * static_cast<T>(scale);
    T y = v.y * static_cast<T>(scale);
    return vector2<T>(x, y);
}

template <meta::arithmetic_type T, meta::arithmetic_type U>
inline vector2<T>
operator*(U scale, vector2<T> const& v)
{
    T x = v.x * scale;
    T y = v.y * scale;
    return vector2<T>(x, y);
}

template <meta::arithmetic_type T>
inline vector2<T>
operator*(vector2<T> const& u, vector2<T> const& v)
{
    T x = u.x * v.x;
    T y = u.y * v.y;
    return vector2<T>(x, y);
}

template <meta::arithmetic_type T>
bool
vector2<T>::normalize(T const eps)
{
    T length = norm();
    if (length > eps)
    {
        T inverted = ((T)1.) / length;

        *this = *this * inverted;
        return true;
    }
    return false;
}
template <meta::arithmetic_type T>
vector2<T>
vector2<T>::normalized(T const eps) const
{
    T length = norm();
    if (length > eps)
    {
        return (*this) / length;
    }
    return {};
}

} // namespace math
} // namespace ivd