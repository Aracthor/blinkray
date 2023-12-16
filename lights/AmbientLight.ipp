constexpr AmbientLight::AmbientLight(const Color& color)
    : Light(color)
{
}

constexpr double AmbientLight::LightPower(const Vector& position, const Vector& normal) const
{
    return 1.0;
}

constexpr double AmbientLight::SpecularPower(const Vector& position, const Vector& reflectionDirection) const
{
    return 0.0;
}

constexpr Optional<Light::RayForShadow> AmbientLight::RayToPosition(const Vector& position) const
{
    return {};
}
