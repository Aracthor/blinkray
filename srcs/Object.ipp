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

constexpr Optional<Object::Intersection> Object::RayIntersection(const Ray& ray) const
{
    const Geometry::DistancesPair distances = m_geometry->GetIntersectionDistances(ray);
    if (distances.first)
    {
        const Vector intersection = ray.AtDistance(*distances.first);
        if (!m_limits || m_limits->Contains(intersection))
            return IntersectionData(ray.origin, intersection);
    }
    if (distances.second)
    {
        const Vector intersection = ray.AtDistance(*distances.second);
        if (!m_limits || m_limits->Contains(intersection))
            return IntersectionData(ray.origin, intersection);
    }
    return {};
}

constexpr Object::Intersection Object::IntersectionData(const Vector& rayOrigin, const Vector& position) const
{
    const Vector normal = m_geometry->GetNormal(rayOrigin, position);
    const Coord2D uv = m_geometry->GetUV(position);
    return {position, normal, uv};
}
