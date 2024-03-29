#pragma once

#include "Light.hpp"

class DirectionalLight final : public Light
{
public:
    constexpr DirectionalLight(const Color& color, const Vector& direction);

    constexpr double LightPower(const Vector& position, const Vector& normal) const override;
    constexpr double SpecularPower(const Vector& position, const Vector& reflectionDirection) const override;
    constexpr Optional<RayForShadow> RayToPosition(const Vector& position) const override;

private:
    Vector m_direction;
};

#include "DirectionalLight.ipp"
