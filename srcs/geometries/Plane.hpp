#pragma once

#include "Geometry.hpp"

class Plane final : public Geometry
{
public:
    constexpr DistancesPair GetIntersectionDistances(const Ray& ray) const override;
    constexpr bool Contains(const Vector& point) const override;
    constexpr Vector GetNormal(const Vector& position) const override;
    constexpr Coord2D GetUV(const Vector& position) const override;
};

#include "Plane.ipp"