#pragma once

#include "Object.hpp"

class Plane final : public Object
{
public:
    constexpr Plane(const Vector& position, const Color& color);

    constexpr Optional<Vector> Intersection(const Ray& ray) const override;
    constexpr Vector GetNormal(const Vector& rayOrigin, const Vector& position) const override;
};

#include "Plane.ipp"