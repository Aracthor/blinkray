#include "Maths.hpp"

constexpr Vector::Vector()
    : x(0.f)
    , y(0.f)
    , z(0.f)
{
}

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

constexpr float Vector::LengthSq() const
{
    return x * x + y * y + z * z;
}

constexpr float Vector::Length() const
{
    return Maths::sqrt(LengthSq());
}

constexpr Vector Vector::Normalized() const
{
    return *this / Length();
}

constexpr Vector Vector::operator+(const Vector& other) const
{
    return Vector(x + other.x, y + other.y, z + other.z);
}

constexpr Vector Vector::operator-(const Vector& other) const
{
    return Vector(x - other.x, y - other.y, z - other.z);
}

constexpr Vector Vector::operator*(float n) const
{
    return Vector(x * n, y * n, z * n);
}

constexpr Vector Vector::operator/(float n) const
{
    return Vector(x / n, y / n, z / n);
}

constexpr float Vector::dot(const Vector& u, const Vector& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
