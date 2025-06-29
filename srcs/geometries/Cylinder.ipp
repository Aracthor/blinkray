#include "Maths.hpp"
#include "Quadratic.hpp"

constexpr Cylinder::Cylinder(double radius)
    : m_radius(radius)
    , m_radiusSq(radius * radius)
{
}

constexpr Geometry::DistancesPair Cylinder::GetIntersectionDistances(const Ray& ray) const
{
    const double a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
    const double b = 2 * (ray.origin.x * ray.dir.x + ray.origin.y * ray.dir.y);
    const double c = ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y + -m_radiusSq;
    return Quadratic::sortedPositiveResults(a, b, c);
}

constexpr bool Cylinder::Contains(const Vector& point) const
{
    return Vector(point.x, point.y, 0.f).LengthSq() < m_radiusSq;
}

constexpr Vector Cylinder::GetNormal(const Vector& rayOrigin, const Vector& position) const
{
    const double dotProduct = Vector::dot(rayOrigin - position, position);
    const Vector normal = dotProduct > 0.0 ? Vector(position.x, position.y, 0.0) : -Vector(position.x, position.y, 0.0);
    return normal.Normalized();
}

constexpr Coord2D Cylinder::GetUV(const Vector& position) const
{
    const double cos = (position.y > 0 ? position.x : -position.x) / m_radius;
    const double angle = Maths::acos(cos);
    const double u = angle / Maths::_PI_2 * m_radius;
    return {u, position.z};
}
