#pragma once

#include <optional>

#include "Color.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Sphere
{
public:
    constexpr Sphere(const Color& color, float radius);

    constexpr std::optional<Vector> Intersection(const Ray& ray) const;
    constexpr Vector GetNormal(const Vector& position) const;

    constexpr const Color& GetColor() const { return m_color; }

private:
    Color m_color;

    float m_radiusSq;
};

#include "Sphere.ipp"
