constexpr Object::Object(const Geometry& geometry, const Vector& position, const Matrix& rotation,
                         const Material& material, const Limits* limits)
    : m_geometry(&geometry)
    , m_position(position)
    , m_rotation(rotation)
    , m_invertRotation(rotation.Invert())
    , m_material(&material)
    , m_limits(limits)
{
}

constexpr std::pair<Optional<Object::Intersection>, Optional<Object::Intersection>>
Object::RayIntersection(const Ray& ray) const
{
    std::pair<Optional<Object::Intersection>, Optional<Object::Intersection>> result{};
    const Geometry::DistancesPair distances = m_geometry->GetIntersectionDistances(ray);
    if (distances.first)
    {
        const Vector intersection = ray.AtDistance(*distances.first);
        if (!m_limits || m_limits->Contains(intersection))
            result.first = IntersectionData(ray.origin, intersection);
    }
    if (distances.second)
    {
        const Vector intersection = ray.AtDistance(*distances.second);
        if (!m_limits || m_limits->Contains(intersection))
            result.second = IntersectionData(ray.origin, intersection);
    }
    return result;
}

constexpr Object::Intersection Object::IntersectionData(const Vector& rayOrigin, const Vector& position) const
{
    const Vector normal = m_geometry->GetNormal(position);
    const Coord2D uv = m_geometry->GetUV(position);
    const bool entering = Vector::dot(normal, rayOrigin - position) > 0.0;
    return {position, normal, uv, entering};
}
