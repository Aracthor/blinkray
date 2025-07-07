constexpr Geometry::DistancesPair Plane::GetIntersectionDistances(const Ray& ray) const
{
    if (std::abs(ray.dir.z) <= 0.001)
        return {};
    const double t = -ray.origin.z / ray.dir.z;
    if (t <= 0)
        return {};
    return {Optional<double>(t), {}};
}

constexpr bool Plane::Contains(const Vector& point) const
{
    return false;
}

constexpr Vector Plane::GetNormal(const Vector& position) const
{
    return Vector(0.0, 0.0, 1.0);
}

constexpr Coord2D Plane::GetUV(const Vector& position) const
{
    return {position.x, position.y};
}
