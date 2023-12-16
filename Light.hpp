#pragma once

#include "Color.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Light
{
public:
    struct RayForShadow
    {
        Ray ray{};
        double maxDistanceSq{};
    };

    constexpr Light(const Color& color)
        : m_color(color)
    {
    }

    constexpr const Color& GetColor() const { return m_color; }

    constexpr virtual double LightPower(const Vector& position, const Vector& normal) const = 0;
    constexpr virtual double SpecularPower(const Vector& position, const Vector& reflectionDirection) const = 0;
    constexpr virtual Optional<RayForShadow> RayToPosition(const Vector& position) const = 0;

private:
    Color m_color;
};
