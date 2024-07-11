#pragma once

#include "Object.hpp"

class Plane final : public Object
{
public:
    constexpr Plane(const Vector& position, const Matrix& rotation, const Material& material);

    constexpr DistancesPair GetIntersectionDistances(const Ray& ray) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;
    constexpr Coord2D GetUV(const Vector& position) const override;
};

#include "Plane.ipp"