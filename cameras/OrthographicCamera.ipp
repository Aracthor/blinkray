constexpr OrthographicCamera::OrthographicCamera(const Vector& position, const Matrix& rotation, float width,
                                                 float height)
    : Camera(position, rotation)
    , m_width(width)
    , m_height(height)
{
}

constexpr Ray OrthographicCamera::GetRay(float pixelX, float pixelY) const
{
    const float posX = pixelX * m_width;
    const float posY = pixelY * m_height;
    const Vector origin = Vector(0.f, posX, posY);
    const Vector target = Vector(1.f, 0.f, 0.f);
    return {origin, target.Normalized()};
}
