#include "Maths.hpp"

constexpr Vector::Vector()
    : x(0.0)
    , y(0.0)
    , z(0.0)
{
}

constexpr Vector::Vector(double x, double y, double z)
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

constexpr double Vector::LengthSq() const
{
    return x * x + y * y + z * z;
}

constexpr double Vector::Length() const
{
    return Maths::sqrt(LengthSq());
}

constexpr Vector Vector::Normalized() const
{
    return *this / Length();
}

constexpr Vector Vector::operator-() const
{
    return Vector(-x, -y, -z);
}

constexpr Vector Vector::operator+(const Vector& other) const
{
    return Vector(x + other.x, y + other.y, z + other.z);
}

constexpr Vector Vector::operator-(const Vector& other) const
{
    return Vector(x - other.x, y - other.y, z - other.z);
}

constexpr Vector Vector::operator*(double n) const
{
    return Vector(x * n, y * n, z * n);
}

constexpr Vector Vector::operator/(double n) const
{
    return Vector(x / n, y / n, z / n);
}

constexpr double Vector::dot(const Vector& u, const Vector& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

constexpr Vector Vector::reflection(const Vector& dir, const Vector& normal)
{
    return dir - normal * 2 * dot(dir, normal);
}
