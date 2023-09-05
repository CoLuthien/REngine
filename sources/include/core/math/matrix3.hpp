
#pragma once

#include "core/definitions.hpp"
#include "constants.hpp"
#include "vector.hpp"

namespace ivd
{
namespace math
{

template <typename T>
struct matrix3
{
public:
    using row_type = vector3<T>;

public:
    constexpr matrix3() = default;
    constexpr matrix3(T value);
    constexpr matrix3(T diag0, T diag1, T diag2);

    // outer product of two vector..
    constexpr explicit matrix3(vector3<T> const& p, vector3<T> const& q);
    constexpr matrix3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22);
    constexpr matrix3(row_type const& p,
                      row_type const& q,
                      row_type const& r,
                      bool            column_vector = false);

public:
    static constexpr matrix3 zero() { return matrix3(0); }
    static constexpr matrix3 identiry() { return matrix3(1, 1, 1); }

public:
    vector3<T> u{}, v{}, w{}; // as row vector
};

template <typename T>
constexpr matrix3<T>::matrix3(T value) : u(value), v(value), w(value)
{
}

template <typename T>
constexpr matrix3<T>::matrix3(T diag0, T diag1, T diag2)
    : u(diag0, 0, 0), v(0, diag1, 0), w(0, 0, diag2)
{
}
template <typename T>
constexpr matrix3<T>::matrix3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)
    : u(m00, m01, m02), //
      v(m10, m11, m12), //
      w(m20, m21, m22)
{
}

template <typename T>
constexpr matrix3<T>::matrix3(vector3<T> const& p, vector3<T> const& q)
    : u(p.x * q.x, p.x * q.y, p.x * q.z), //
      v(p.y * q.x, p.y * q.y, p.y * q.z), //
      w(p.z * q.x, p.z * q.y, p.z * q.z)
{
}

template <typename T>
constexpr matrix3<T>::matrix3(row_type const& p,
                              row_type const& q,
                              row_type const& r,
                              bool            column_vector)
{
    if (column_vector)
    {
        u = row_type{p.x, q.x, r.x};
        v = row_type{p.y, q.y, r.y};
        w = row_type{p.z, q.z, r.z};
    }
    else
    {
        u = p;
        v = q;
        w = r;
    }
}

} // namespace math

} // namespace ivd