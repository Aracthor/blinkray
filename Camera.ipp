constexpr Camera::Camera(const Vector& position, float fowWidth, float fowHeight, float fowDistance)
    : m_position(position)
    , m_fowWidth(fowWidth)
    , m_fowHeight(fowHeight)
    , m_fowDistance(fowDistance)
{
}

constexpr Ray Camera::GetRay(float pixelX, float pixelY) const
{
    const float targetX = m_fowDistance;
    const float targetY = pixelX * m_fowWidth;
    const float targetZ = pixelY * m_fowHeight;
    const Vector target = Vector(targetX, targetY, targetZ);
    return {m_position, target.Normalized()};
}
