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

constexpr std::pair<Optional<Vector>, Optional<Vector>> Object::RayIntersection(const Ray& ray) const
{
    std::pair<Optional<Vector>, Optional<Vector>> result{};
    const Geometry::DistancesPair distances = m_geometry->GetIntersectionDistances(ray);
    if (distances.first)
    {
        const Vector intersection = ray.AtDistance(*distances.first);
        if (!m_limits || m_limits->Contains(intersection))
            result.first = intersection;
    }
    if (distances.second)
    {
        const Vector intersection = ray.AtDistance(*distances.second);
        if (!m_limits || m_limits->Contains(intersection))
            result.second = intersection;
    }
    return result;
}
