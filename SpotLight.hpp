#pragma once

#include "Ray.hpp"
#include "Vector.hpp"

class SpotLight
{
public:
    constexpr SpotLight(const Vector& position, float power);

    constexpr float LightPower(const Vector& position, const Vector& normal) const;
    constexpr Ray RayToPosition(const Vector& position) const;

private:
    Vector m_position;
    float m_power;
};

#include "SpotLight.ipp"
