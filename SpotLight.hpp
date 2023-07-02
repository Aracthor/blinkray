#pragma once

#include "Vector.hpp"

class SpotLight
{
public:
    constexpr SpotLight(const Vector& position, float power);

    constexpr float LightPower(const Vector& position, const Vector& normal) const;

private:
    Vector m_position;
    float m_power;
};

#include "SpotLight.ipp"
