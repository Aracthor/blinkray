#pragma once

#include "Object.hpp"

class Cone final : public Object
{
public:
    constexpr Cone(const Vector& position, const Matrix& repere, const Material& material,
                   float angle);

    constexpr Optional<float> IntersectionDistance(const Ray& ray) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;
    constexpr Coord2D GetUV(const Vector& position) const override;

private:
    float m_squaredCos;
    float m_squaredSin;
    float m_atan;
};

#include "Cone.ipp"