#include "Maths.hpp"
#include "Quadratic.hpp"

constexpr Cone::Cone(const Vector& position, const Matrix& rotation, const Material& material,
                     float angle)
    : Object(position, rotation, material)
    , m_sin(Maths::sin(angle))
    , m_squaredCos(Maths::pow(Maths::cos(angle), 2))
    , m_squaredSin(Maths::pow(Maths::sin(angle), 2))
    , m_atan(Maths::atan(Maths::_PI_2 - angle))
{
}

constexpr Optional<float> Cone::IntersectionDistance(const Ray& ray) const
{
    const float a = m_squaredCos * (ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y) -
                    m_squaredSin * (ray.dir.z * ray.dir.z);
    const float b = 2 * m_squaredCos * (ray.origin.x * ray.dir.x + ray.origin.y * ray.dir.y) -
                    2 * m_squaredSin * (ray.origin.z * ray.dir.z);
    const float c = m_squaredCos * (ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y) -
                    m_squaredSin * (ray.origin.z * ray.origin.z);
    return Quadratic::shortestPositiveResult(a, b, c);
}

constexpr Vector Cone::GetNormal(const Vector& rayOrigin, const Vector& position) const
{
    if (position.x == 0.f && position.y == 0.f)
        return {0.f, 0.f, 1.f}; // Absurd normal for an absurd case.
    const float z = m_atan * (Maths::sqrt(position.x * position.x + position.y * position.y));
    return Vector(position.x, position.y, z);
}

constexpr Coord2D Cone::GetUV(const Vector& position) const
{
    const float radius = m_sin * position.z;
    const float cos = (position.y > 0 ? position.x : -position.x) / radius;
    const float angle = Maths::acos(cos);
    const float u = angle / Maths::_PI_2;
    return {u, position.z};
}