#pragma once

#include "Camera.hpp"

class PerspectiveCamera final : public Camera
{
public:
    constexpr PerspectiveCamera(const Vector& position, const Matrix& rotation, double fowWidth, double fowHeight,
                                double fowDistance);

    // Both of those params are between -0.5 and 0.5
    constexpr Ray GetRay(double pixelX, double pixelY) const override;

private:
    double m_fowWidth;
    double m_fowHeight;
    double m_fowDistance;
};

#include "PerspectiveCamera.ipp"
