#pragma once

#include "Light.hpp"

class SpotLight final : public Light
{
public:
    constexpr SpotLight(const Color& color, const Vector& position, float power);

    constexpr float LightPower(const Vector& position, const Vector& normal) const override;
    constexpr float SpecularPower(const Vector& position, const Vector& reflectionDirection) const override;
    constexpr Optional<RayForShadow> RayToPosition(const Vector& position) const override;

private:
    Vector m_position;
    float m_power;
};

#include "SpotLight.ipp"
