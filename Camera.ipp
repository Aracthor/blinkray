constexpr Camera::Camera(const Vector& position, const Matrix& rotation, float fowWidth, float fowHeight,
                         float fowDistance)
    : m_position(position)
    , m_invertRotation(rotation.Invert())
    , m_fowWidth(fowWidth)
    , m_fowHeight(fowHeight)
    , m_fowDistance(fowDistance)
{
}

constexpr Ray Camera::GetRay(float pixelX, float pixelY) const
{
    const Vector origin = {0.f, 0.f, 0.f};
    const float targetX = m_fowDistance;
    const float targetY = pixelX * m_fowWidth;
    const float targetZ = pixelY * m_fowHeight;
    const Vector target = Vector(targetX, targetY, targetZ);
    const Ray ray = {origin, target.Normalized()};
    return ray.Transform(-m_position, m_invertRotation);
}
