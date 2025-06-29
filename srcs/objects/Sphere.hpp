#pragma once

#include "Object.hpp"

class Sphere final : public Object
{
public:
    constexpr Sphere(const Vector& position, const Matrix& repere, const Material& material, double radius,
                     const Limits* limits = nullptr);

    constexpr DistancesPair GetIntersectionDistances(const Ray& ray) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;
    constexpr Coord2D GetUV(const Vector& position) const override;

private:
    double m_radiusSq;
};

#include "Sphere.ipp"