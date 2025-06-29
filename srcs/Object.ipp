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

constexpr Optional<double> Object::IntersectionDistance(const Ray& ray) const
{
    const Geometry::DistancesPair distances = m_geometry->GetIntersectionDistances(ray);
    if (distances.first && (!m_limits || m_limits->Contains(ray.AtDistance(*distances.first))))
        return distances.first;
    else if (distances.second && (!m_limits || m_limits->Contains(ray.AtDistance(*distances.second))))
        return distances.second;
    return {};
}
