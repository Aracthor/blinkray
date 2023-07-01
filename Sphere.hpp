#pragma once

#include <optional>

#include "Vector.hpp"

class Sphere
{
public:
    constexpr Sphere(float radius);

    constexpr std::optional<Vector> Intersection(const Vector& origin,
                                                 const Vector& direction) const;

private:
    float m_radiusSq;
};

#include "Sphere.ipp"
