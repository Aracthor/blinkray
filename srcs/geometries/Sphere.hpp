#pragma once

#include "Geometry.hpp"

class Sphere final : public Geometry
{
public:
    constexpr Sphere(double radius);

    constexpr DistancesPair GetIntersectionDistances(const Ray& ray) const override;
    constexpr bool Contains(const Vector& point) const override;
    constexpr Vector GetNormal(const Vector& position) const override;
    constexpr Coord2D GetUV(const Vector& position) const override;

private:
    double m_radiusSq;
};

#include "Sphere.ipp"
