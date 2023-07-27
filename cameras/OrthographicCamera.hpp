#pragma once

#include "Camera.hpp"

class OrthographicCamera final : public Camera
{
public:
    constexpr OrthographicCamera(const Vector& position, const Matrix& rotation, float width, float height);

    // Both of those params are between -0.5 and 0.5
    constexpr Ray GetRay(float pixelX, float pixelY) const override;

private:
    float m_width;
    float m_height;
};

#include "OrthographicCamera.ipp"
