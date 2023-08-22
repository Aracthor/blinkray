constexpr Object::Object(const Vector& position, const Matrix& rotation, const Limits& limits, const Material& material)
    : m_position(position)
    , m_rotation(rotation)
    , m_invertRotation(rotation.Invert())
    , m_limits(limits)
    , m_material(material)
{
}

constexpr Optional<float> Object::IntersectionDistance(const Ray& ray) const
{
    const DistancesPair distances = GetIntersectionDistances(ray);
    if (distances.first && m_limits.Contains(ray.AtDistance(*distances.first)))
        return distances.first;
    else if (distances.second && m_limits.Contains(ray.AtDistance(*distances.second)))
        return distances.second;
    return {};
}
