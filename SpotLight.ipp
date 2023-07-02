constexpr SpotLight::SpotLight(const Vector& position, float power)
    : m_position(position)
    , m_power(power)
{
}

constexpr float SpotLight::LightPower(const Vector& position, const Vector& normal) const
{
    const Vector lightToPosition = m_position - position;
    const float distance = lightToPosition.Length();
    const float dotProduct = Vector::dot(normal, lightToPosition);
    const float cosAngle = dotProduct / (normal.Length() * distance);
    if (cosAngle < 0.0f)
        return 0.0f;
    return m_power / distance * cosAngle;
}
