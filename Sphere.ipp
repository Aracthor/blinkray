#include "Quadratic.hpp"

constexpr Sphere::Sphere(float radius, const Color& color)
    : m_radiusSq(radius * radius)
    , m_color(color)
{
}

constexpr std::optional<Vector> Sphere::Intersection(const Vector& origin, const Vector& dir) const
{
    const float a = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    const float b = 2 * (origin.x * dir.x + origin.y * dir.y + origin.z * dir.z);
    const float c = origin.x * origin.x + origin.y * origin.y + origin.z * origin.z - m_radiusSq;
    float result1 = 0.f, result2 = 0.f;
    const int intersectionCount = Quadratic::solve(a, b, c, result1, result2);
    if (intersectionCount == 0)
        return {};
    if (intersectionCount == 1)
        return result1 > 0.f ? (origin + dir * result1) : std::optional<Vector>();

    if (result1 < 0.f && result2 < 0.f)
        return {};
    if (result1 < 0.f)
        return origin + dir * result2;
    if (result2 < 0.f)
        return origin + dir * result1;
    const float closestResult = std::min(result1, result2);
    return origin + dir * closestResult;
}

constexpr Vector Sphere::GetNormal(const Vector& position) const
{
    return position;
}
