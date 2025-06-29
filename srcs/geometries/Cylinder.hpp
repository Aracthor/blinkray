#pragma once

#include "Geometry.hpp"

class Cylinder final : public Geometry
{
public:
    constexpr Cylinder(double radius);

    constexpr DistancesPair GetIntersectionDistances(const Ray& ray) const override;
    constexpr bool Contains(const Vector& point) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;
    constexpr Coord2D GetUV(const Vector& position) const override;

private:
    double m_radius;
    double m_radiusSq;
};

#include "Cylinder.ipp"
