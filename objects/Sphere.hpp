#pragma once

#include "Object.hpp"

class Sphere final : public Object
{
public:
    constexpr Sphere(const Vector& position, const Matrix& repere, const Limits& limits, const Material& material,
                     float radius);

    constexpr DistancesPair GetIntersectionDistances(const Ray& ray) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;
    constexpr Coord2D GetUV(const Vector& position) const override;

private:
    float m_radiusSq;
};

#include "Sphere.ipp"