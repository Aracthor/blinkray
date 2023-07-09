#pragma once

#include "Object.hpp"

class Cylinder final : public Object
{
public:
    constexpr Cylinder(const Vector& position, const Matrix& repere, const Color& color,
                       float radius);

    constexpr Optional<float> IntersectionDistance(const Ray& ray) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;

private:
    float m_radiusSq;
};

#include "Cylinder.ipp"