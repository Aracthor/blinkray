#pragma once

#include "Matrix.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Camera
{
public:
    constexpr Camera(const Vector& position, const Matrix& rotation);

    constexpr const Vector& Position() const { return m_position; }
    constexpr const Matrix& InvertRotation() const { return m_invertRotation; }

    // Both of those params are between -0.5 and 0.5
    virtual constexpr Ray GetRay(float pixelX, float pixelY) const = 0;

private:
    Vector m_position;
    Matrix m_invertRotation;
};

#include "Camera.ipp"
