constexpr PerspectiveCamera::PerspectiveCamera(const Vector& position, const Matrix& rotation, double fowWidth,
                                               double fowHeight, double fowDistance)
    : Camera(position, rotation)
    , m_fowWidth(fowWidth)
    , m_fowHeight(fowHeight)
    , m_fowDistance(fowDistance)
{
}

constexpr Ray PerspectiveCamera::GetRay(double pixelX, double pixelY) const
{
    const Vector origin = {0.0, 0.0, 0.0};
    const double targetX = m_fowDistance;
    const double targetY = pixelX * m_fowWidth;
    const double targetZ = pixelY * m_fowHeight;
    const Vector target = Vector(targetX, targetY, targetZ);
    return {origin, target.Normalized()};
}
