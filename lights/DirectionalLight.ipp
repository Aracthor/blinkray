#include <limits>

constexpr DirectionalLight::DirectionalLight(const Color& color, const Vector& direction)
    : Light(color)
    , m_direction(direction.Normalized())
{
}

constexpr float DirectionalLight::LightPower(const Vector& position, const Vector& normal) const
{
    const float dotProduct = Vector::dot(normal, -m_direction);
    const float cosAngle = dotProduct / (normal.Length());
    if (cosAngle < 0.0f)
        return 0.0f;
    return cosAngle;
}

constexpr float DirectionalLight::SpecularPower(const Vector& position, const Vector& reflectionDirection) const
{
    const float specularPower = Vector::dot(reflectionDirection, -m_direction);
    return specularPower > 0.f ? Maths::pow(specularPower, 6.f) : 0.f;
}

constexpr Optional<Light::RayForShadow> DirectionalLight::RayToPosition(const Vector& position) const
{
    const Vector rayStart = position - m_direction * 0.001;
    return Optional<Light::RayForShadow>({{rayStart, -m_direction}, std::numeric_limits<float>::max()});
}
