#pragma once

#include "Object.hpp"

class Cylinder final : public Object
{
public:
    constexpr Cylinder(const Vector& position, const Matrix& repere, const Limits& limits, const Material& material,
                       float radius);

    constexpr DistancesPair GetIntersectionDistances(const Ray& ray) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;
    constexpr Coord2D GetUV(const Vector& position) const override;

private:
    float m_radius;
    float m_radiusSq;
};

#include "Cylinder.ipp"