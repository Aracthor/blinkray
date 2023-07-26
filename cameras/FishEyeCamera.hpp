#pragma once

#include "Camera.hpp"

class FishEyeCamera final : public Camera
{
public:
    constexpr FishEyeCamera(const Vector& position, const Matrix& rotation, float azimuthAngle, float siteAngle);

    // Both of those params are between -0.5 and 0.5
    constexpr Ray GetRay(float pixelX, float pixelY) const override;

private:
    float m_azimuthAngle;
    float m_siteAngle;
};

#include "FishEyeCamera.ipp"
