#include "Quadratic.hpp"

constexpr Sphere::Sphere(double radius)
    : m_radiusSq(radius * radius)
{
}

constexpr Geometry::DistancesPair Sphere::GetIntersectionDistances(const Ray& ray) const
{
    const double a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z;
    const double b = 2 * (ray.origin.x * ray.dir.x + ray.origin.y * ray.dir.y + ray.origin.z * ray.dir.z);
    const double c =
        ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y + ray.origin.z * ray.origin.z - m_radiusSq;
    return Quadratic::sortedPositiveResults(a, b, c);
}

constexpr bool Sphere::Contains(const Vector& point) const
{
    return point.LengthSq() < m_radiusSq;
}

constexpr Vector Sphere::GetNormal(const Vector& rayOrigin, const Vector& position) const
{
    const double dotProduct = Vector::dot(rayOrigin - position, position);
    const Vector normal = (dotProduct > 0.0) ? position.Normalized() : -position.Normalized();
    return normal.Normalized();
}

constexpr Coord2D Sphere::GetUV(const Vector& position) const
{
    // We need a reliable atan2 function to make a correct spherical UV mapping.
    return {position.y, position.z};
}
