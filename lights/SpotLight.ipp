constexpr SpotLight::SpotLight(const Color& color, const Vector& position, float power)
    : Light(color)
    , m_position(position)
    , m_power(power)
{
}

constexpr float SpotLight::LightPower(const Vector& position, const Vector& normal) const
{
    const Vector positionToLight = m_position - position;
    const float distance = positionToLight.Length();
    const float dotProduct = Vector::dot(normal, positionToLight);
    const float cosAngle = dotProduct / (normal.Length() * distance);
    if (cosAngle < 0.0f)
        return 0.0f;
    return m_power / distance * cosAngle;
}

constexpr float SpotLight::SpecularPower(const Vector& position, const Vector& reflectionDirection) const
{
    const Vector positionToLight = m_position - position;
    const float distance = positionToLight.Length();
    const float specularPower = Vector::dot(reflectionDirection, positionToLight / distance);
    return specularPower > 0.f ? m_power / distance * Maths::pow(specularPower, 6.f) : 0.f;
}

constexpr Optional<Light::RayForShadow> SpotLight::RayToPosition(const Vector& position) const
{
    const Vector positionToLight = m_position - position;
    const float distanceSq = positionToLight.LengthSq();
    const Vector directionNormalized = positionToLight.Normalized();
    const Vector rayStart = position + directionNormalized * 0.001;
    return Optional<Light::RayForShadow>({{rayStart, directionNormalized}, distanceSq});
}
