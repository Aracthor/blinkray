#pragma once

#include "Camera.hpp"

class OrthographicCamera final : public Camera
{
public:
    constexpr OrthographicCamera(const Vector& position, const Matrix& rotation, double width, double height);

    // Both of those params are between -0.5 and 0.5
    constexpr Ray GetRay(double pixelX, double pixelY) const override;

private:
    double m_width;
    double m_height;
};

#include "OrthographicCamera.ipp"
