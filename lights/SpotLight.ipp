constexpr SpotLight::SpotLight(const Color& color, const Vector& position, double power)
    : Light(color)
    , m_position(position)
    , m_power(power)
{
}

constexpr double SpotLight::LightPower(const Vector& position, const Vector& normal) const
{
    const Vector positionToLight = m_position - position;
    const double distance = positionToLight.Length();
    const double dotProduct = Vector::dot(normal, positionToLight);
    const double cosAngle = dotProduct / (normal.Length() * distance);
    if (cosAngle < 0.0)
        return 0.0;
    return m_power / distance * cosAngle;
}

constexpr double SpotLight::SpecularPower(const Vector& position, const Vector& reflectionDirection) const
{
    const Vector positionToLight = m_position - position;
    const double distance = positionToLight.Length();
    const double specularPower = Vector::dot(reflectionDirection, positionToLight / distance);
    return specularPower > 0.0 ? m_power / distance * Maths::pow(specularPower, 6.0) : 0.0;
}

constexpr Optional<Light::RayForShadow> SpotLight::RayToPosition(const Vector& position) const
{
    const Vector positionToLight = m_position - position;
    const double distanceSq = positionToLight.LengthSq();
    const Vector directionNormalized = positionToLight.Normalized();
    const Vector rayStart = position + directionNormalized * 0.001;
    return Optional<Light::RayForShadow>({{rayStart, directionNormalized}, distanceSq});
}
