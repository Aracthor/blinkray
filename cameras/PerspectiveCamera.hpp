#pragma once

#include "Camera.hpp"

class PerspectiveCamera final : public Camera
{
public:
    constexpr PerspectiveCamera(const Vector& position, const Matrix& rotation, float fowWidth, float fowHeight,
                                float fowDistance);

    // Both of those params are between -0.5 and 0.5
    constexpr Ray GetRay(float pixelX, float pixelY) const override;

private:
    float m_fowWidth;
    float m_fowHeight;
    float m_fowDistance;
};

#include "PerspectiveCamera.ipp"
