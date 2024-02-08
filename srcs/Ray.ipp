constexpr Ray Ray::Transform(const Vector& position, const Matrix& invertRotation) const
{
    const Vector translatedPosition = origin - position;
    const Vector newPosition = invertRotation * translatedPosition;
    const Vector newDirection = invertRotation * dir;
    return {newPosition, newDirection};
}

constexpr Vector Ray::AtDistance(double distance) const
{
    return origin + dir * distance;
}
