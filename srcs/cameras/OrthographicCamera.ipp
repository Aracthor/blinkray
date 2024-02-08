constexpr OrthographicCamera::OrthographicCamera(const Vector& position, const Matrix& rotation, double width,
                                                 double height)
    : Camera(position, rotation)
    , m_width(width)
    , m_height(height)
{
}

constexpr Ray OrthographicCamera::GetRay(double pixelX, double pixelY) const
{
    const double posX = pixelX * m_width;
    const double posY = pixelY * m_height;
    const Vector origin = Vector(0.0, posX, posY);
    const Vector target = Vector(1.0, 0.0, 0.0);
    return {origin, target.Normalized()};
}
