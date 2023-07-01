#include "Maths.hpp"

constexpr Vector::Vector(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z)
{
}

constexpr Vector::Vector(const Vector& other)
    : x(other.x)
    , y(other.y)
    , z(other.z)
{
}

constexpr Vector Vector::operator+(const Vector& other) const
{
    return Vector(x + other.x, y + other.y, z + other.z);
}

constexpr Vector Vector::operator*(float n) const
{
    return Vector(x * n, y * n, z * n);
}

constexpr Vector Vector::operator/(float n) const
{
    return Vector(x / n, y / n, z / n);
}
