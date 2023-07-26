#pragma once

#include "Color.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class SpotLight
{
public:
    constexpr SpotLight(const Color& color, const Vector& position, float power);

    constexpr float LightPower(const Vector& position, const Vector& normal) const;
    constexpr float SpecularPower(const Vector& position, const Vector& reflectionDirection) const;
    constexpr Ray RayToPosition(const Vector& position) const;

    constexpr const Color& GetColor() const { return m_color; }

private:
    Color m_color;
    Vector m_position;
    float m_power;
};

#include "SpotLight.ipp"
