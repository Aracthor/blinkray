constexpr Camera::Camera(const Vector& position, const Matrix& rotation)
    : m_position(position)
    , m_invertRotation(rotation.Invert())
{
}
