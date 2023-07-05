constexpr Ray Ray::Transform(const Vector& translation) const
{
    return {origin - translation, dir};
}

constexpr Vector Ray::AtDistance(float distance) const
{
    return origin + dir * distance;
}
