#pragma once

#include <optional>

#include "Color.hpp"
#include "Vector.hpp"

class Sphere
{
public:
    constexpr Sphere(float radius, const Color& color);

    constexpr std::optional<Vector> Intersection(const Vector& origin,
                                                 const Vector& direction) const;
    constexpr Vector GetNormal(const Vector& position) const;

    constexpr const Color& GetColor() const { return m_color; }

private:
    float m_radiusSq;
    Color m_color;
};

#include "Sphere.ipp"
