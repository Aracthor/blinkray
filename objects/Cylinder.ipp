#include "Maths.hpp"
#include "Quadratic.hpp"

constexpr Cylinder::Cylinder(const Vector& position, const Matrix& rotation, const Material& material, float radius)
    : Object(position, rotation, material)
    , m_radius(radius)
    , m_radiusSq(radius * radius)
{
}

constexpr Optional<float> Cylinder::IntersectionDistance(const Ray& ray) const
{
    const float a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
    const float b = 2 * (ray.origin.x * ray.dir.x + ray.origin.y * ray.dir.y);
    const float c = ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y + -m_radiusSq;
    return Quadratic::shortestPositiveResult(a, b, c);
}

constexpr Vector Cylinder::GetNormal(const Vector& rayOrigin, const Vector& position) const
{
    return {position.x, position.y, 0.f};
}

constexpr Coord2D Cylinder::GetUV(const Vector& position) const
{
    const float cos = (position.y > 0 ? position.x : -position.x) / m_radius;
    const float angle = Maths::acos(cos);
    const float u = angle / Maths::_PI_2 * m_radius;
    return {u, position.z};
}
