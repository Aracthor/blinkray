#pragma once

#include "Color.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Object
{
public:
    constexpr Object(const Vector& position, const Color& color)
        : m_position(position)
        , m_color(color)
    {
    }

    constexpr const Vector& GetPosition() const { return m_position; }
    constexpr const Color& GetColor() const { return m_color; }

    constexpr virtual Optional<Vector> Intersection(const Ray& ray) const = 0;
    constexpr virtual Vector GetNormal(const Vector& position) const = 0;

private:
    Vector m_position;
    Color m_color;
};
