#include "Quadratic.hpp"

constexpr Sphere::Sphere(const Vector& position, const Matrix& rotation, const Material& material,
                         float radius)
    : Object(position, rotation, material)
    , m_radiusSq(radius * radius)
{
}

constexpr Optional<float> Sphere::IntersectionDistance(const Ray& ray) const
{
    const float a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z;
    const float b =
        2 * (ray.origin.x * ray.dir.x + ray.origin.y * ray.dir.y + ray.origin.z * ray.dir.z);
    const float c = ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y +
                    ray.origin.z * ray.origin.z - m_radiusSq;
    return Quadratic::shortestPositiveResult(a, b, c);
}

constexpr Vector Sphere::GetNormal(const Vector& rayOrigin, const Vector& position) const
{
    return position;
}

constexpr Coord2D Sphere::GetUV(const Vector& position) const
{
    // TODO
    return {position.x, position.y};
}
