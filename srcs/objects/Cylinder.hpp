#pragma once

#include "Object.hpp"

class Cylinder final : public Object
{
public:
    constexpr Cylinder(const Vector& position, const Matrix& repere, const Material& material, double radius);

    constexpr DistancesPair GetIntersectionDistances(const Ray& ray) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;
    constexpr Coord2D GetUV(const Vector& position) const override;

private:
    double m_radius;
    double m_radiusSq;
};

#include "Cylinder.ipp"