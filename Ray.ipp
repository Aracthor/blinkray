constexpr Ray Ray::Transform(const Vector& translation) const
{
    return {origin - translation, dir};
}
