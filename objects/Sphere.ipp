#include "Quadratic.hpp"

constexpr Sphere::Sphere(const Vector& position, const Matrix& rotation, const Limits& limits, const Material& material,
                         float radius)
    : Object(position, rotation, limits, material)
    , m_radiusSq(radius * radius)
{
}

constexpr Object::DistancesPair Sphere::GetIntersectionDistances(const Ray& ray) const
{
    const float a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z;
    const float b = 2 * (ray.origin.x * ray.dir.x + ray.origin.y * ray.dir.y + ray.origin.z * ray.dir.z);
    const float c =
        ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y + ray.origin.z * ray.origin.z - m_radiusSq;
    return Quadratic::sortedPositiveResults(a, b, c);
}

constexpr Vector Sphere::GetNormal(const Vector& rayOrigin, const Vector& position) const
{
    const float dotProduct = Vector::dot(rayOrigin - position, position);
    return (dotProduct > 0.f) ? position : -position;
}

constexpr Coord2D Sphere::GetUV(const Vector& position) const
{
    // We need a reliable atan2 function to make a correct spherical UV mapping.
    return {position.y, position.z};
}
