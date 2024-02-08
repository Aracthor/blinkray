#include "Maths.hpp"

constexpr FishEyeCamera::FishEyeCamera(const Vector& position, const Matrix& rotation, double azimuthAngle,
                                       double siteAngle)
    : Camera(position, rotation)
    , m_azimuthAngle(azimuthAngle)
    , m_siteAngle(siteAngle)
{
}

constexpr Ray FishEyeCamera::GetRay(double pixelX, double pixelY) const
{
    const Vector origin = {0.0, 0.0, 0.0};

    const double azimuthAngle = pixelX * m_azimuthAngle;
    const double siteAngle = pixelY * m_siteAngle;
    const double cosY = Maths::cos(siteAngle);
    const double targetX = cosY * Maths::cos(azimuthAngle);
    const double targetY = cosY * Maths::sin(azimuthAngle);
    const double targetZ = Maths::sin(siteAngle);
    const Vector target = Vector(targetX, targetY, targetZ);
    return {origin, target.Normalized()};
}
