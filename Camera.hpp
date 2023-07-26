#pragma once

#include "Matrix.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Camera
{
public:
    constexpr Camera(const Vector& position, const Matrix& rotation, float fowWidth, float fowHeight,
                     float fowDistance);

    // Both of those params are between -0.5 and 0.5
    constexpr Ray GetRay(float pixelX, float pixelY) const;

private:
    Vector m_position;
    Matrix m_invertRotation;
    float m_fowWidth;
    float m_fowHeight;
    float m_fowDistance;
};

#include "Camera.ipp"
