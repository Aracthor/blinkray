#include <limits>

constexpr DirectionalLight::DirectionalLight(const Color& color, const Vector& direction)
    : Light(color)
    , m_direction(direction.Normalized())
{
}

constexpr double DirectionalLight::LightPower(const Vector& position, const Vector& normal) const
{
    const double dotProduct = Vector::dot(normal, -m_direction);
    const double cosAngle = dotProduct / (normal.Length());
    if (cosAngle < 0.0)
        return 0.0;
    return cosAngle;
}

constexpr double DirectionalLight::SpecularPower(const Vector& position, const Vector& reflectionDirection) const
{
    const double specularPower = Vector::dot(reflectionDirection, -m_direction);
    return specularPower > 0.0 ? Maths::pow(specularPower, 6.0) : 0.0;
}

constexpr Optional<Light::RayForShadow> DirectionalLight::RayToPosition(const Vector& position) const
{
    const Vector rayStart = position - m_direction * 0.001;
    return Optional<Light::RayForShadow>({{rayStart, -m_direction}, std::numeric_limits<double>::max()});
}
