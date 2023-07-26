#include "Maths.hpp"

constexpr FishEyeCamera::FishEyeCamera(const Vector& position, const Matrix& rotation, float azimuthAngle,
                                       float siteAngle)
    : Camera(position, rotation)
    , m_azimuthAngle(azimuthAngle)
    , m_siteAngle(siteAngle)
{
}

constexpr Ray FishEyeCamera::GetRay(float pixelX, float pixelY) const
{
    const Vector origin = {0.f, 0.f, 0.f};

    const float azimuthAngle = pixelX * m_azimuthAngle;
    const float siteAngle = pixelY * m_siteAngle;
    const float cosY = Maths::cos(siteAngle);
    const float targetX = cosY * Maths::cos(azimuthAngle);
    const float targetY = cosY * Maths::sin(azimuthAngle);
    const float targetZ = Maths::sin(siteAngle);
    const Vector target = Vector(targetX, targetY, targetZ);
    return {origin, target.Normalized()};
}
