#pragma once

#include "Ray.hpp"
#include "Vector.hpp"

class Camera
{
public:
    constexpr Camera(const Vector& position, float fowWidth, float fowHeight, float fowDistance);

    // Both of those params are between -0.5 and 0.5
    constexpr Ray GetRay(float pixelX, float pixelY) const;

private:
    Vector m_position;
    float m_fowWidth;
    float m_fowHeight;
    float m_fowDistance;
};

#include "Camera.ipp"
