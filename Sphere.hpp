#pragma once

#include "Object.hpp"

class Sphere final : public Object
{
public:
    constexpr Sphere(const Vector& position, const Color& color, float radius);

    constexpr Optional<Vector> Intersection(const Ray& ray) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;

private:
    float m_radiusSq;
};

#include "Sphere.ipp"