constexpr Ray Ray::Transform(const Vector& position, const Matrix& rotation) const
{
    const Vector translatedPosition = origin - position;
    const Vector newPosition = rotation * translatedPosition;
    const Vector newDirection = rotation * dir;
    return {newPosition, newDirection};
}

constexpr Vector Ray::AtDistance(float distance) const
{
    return origin + dir * distance;
}
