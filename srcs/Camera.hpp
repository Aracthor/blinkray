#pragma once

#include "Matrix.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Camera
{
public:
    constexpr Camera(const Vector& position, const Matrix& rotation);

    constexpr const Vector& Position() const { return m_position; }
    constexpr const Matrix& Rotation() const { return m_rotation; }

    // Both of those params are between -0.5 and 0.5
    virtual constexpr Ray GetRay(double pixelX, double pixelY) const = 0;

private:
    Vector m_position;
    Matrix m_rotation;
};

#include "Camera.ipp"
