#pragma once

#include "Camera.hpp"

class FishEyeCamera final : public Camera
{
public:
    constexpr FishEyeCamera(const Vector& position, const Matrix& rotation, double azimuthAngle, double siteAngle);

    // Both of those params are between -0.5 and 0.5
    constexpr Ray GetRay(double pixelX, double pixelY) const override;

private:
    double m_azimuthAngle;
    double m_siteAngle;
};

#include "FishEyeCamera.ipp"
