#include "Quadratic.hpp"

constexpr Sphere::Sphere(const Vector& position, const Matrix& rotation, const Color& color,
                         float radius)
    : Object(position, rotation, color)
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
    float result1 = 0.f, result2 = 0.f;
    const int intersectionCount = Quadratic::solve(a, b, c, result1, result2);
    if (intersectionCount == 0)
        return {};
    if (intersectionCount == 1)
        return (result1 > 0.f) ? result1 : Optional<Vector>();

    if (result1 < 0.f && result2 < 0.f)
        return {};
    if (result1 < 0.f)
        return result2;
    if (result2 < 0.f)
        return result1;
    return std::min(result1, result2);
}

constexpr Vector Sphere::GetNormal(const Vector& rayOrigin, const Vector& position) const
{
    return position;
}
