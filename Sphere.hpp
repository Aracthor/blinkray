#pragma once

#include "Color.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Sphere
{
public:
    constexpr Sphere(const Vector& position, const Color& color, float radius);

    constexpr Optional<Vector> Intersection(const Ray& ray) const;
    constexpr Vector GetNormal(const Vector& position) const;

    constexpr const Vector& GetPosition() const { return m_position; }
    constexpr const Color& GetColor() const { return m_color; }

private:
    Vector m_position;
    Color m_color;

    float m_radiusSq;
};

#include "Sphere.ipp"
