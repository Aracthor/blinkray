#pragma once

#include "Light.hpp"

class AmbientLight final : public Light
{
public:
    constexpr AmbientLight(const Color& color);

    constexpr double LightPower(const Vector& position, const Vector& normal) const override;
    constexpr double SpecularPower(const Vector& position, const Vector& reflectionDirection) const override;
    constexpr Optional<RayForShadow> RayToPosition(const Vector& position) const override;
};

#include "AmbientLight.ipp"
