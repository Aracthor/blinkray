constexpr Plane::Plane(const Vector& position, const Matrix& rotation, const Limits& limits, const Material& material)
    : Object(position, rotation, limits, material)
{
}

constexpr Object::DistancesPair Plane::GetIntersectionDistances(const Ray& ray) const
{
    if (ray.dir.z == 0.f)
        return {};
    const float t = -ray.origin.z / ray.dir.z;
    if (t <= 0)
        return {};
    return {Optional<float>(t), {}};
}

constexpr Vector Plane::GetNormal(const Vector& rayOrigin, const Vector& position) const
{
    const float z = rayOrigin.z > 0.f ? 1.f : -1.f;
    return Vector(0.f, 0.f, z);
}

constexpr Coord2D Plane::GetUV(const Vector& position) const
{
    return {position.x, position.y};
}
