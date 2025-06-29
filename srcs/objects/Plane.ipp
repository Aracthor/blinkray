constexpr Plane::Plane(const Vector& position, const Matrix& rotation, const Material& material, const Limits* limits)
    : Object(position, rotation, material, limits)
{
}

constexpr Object::DistancesPair Plane::GetIntersectionDistances(const Ray& ray) const
{
    if (ray.dir.z == 0.0)
        return {};
    const double t = -ray.origin.z / ray.dir.z;
    if (t <= 0)
        return {};
    return {Optional<double>(t), {}};
}

constexpr Vector Plane::GetNormal(const Vector& rayOrigin, const Vector& position) const
{
    const double z = rayOrigin.z > 0.0 ? 1.0 : -1.0;
    return Vector(0.0, 0.0, z);
}

constexpr Coord2D Plane::GetUV(const Vector& position) const
{
    return {position.x, position.y};
}
