constexpr AmbientLight::AmbientLight(const Color& color)
    : Light(color)
{
}

constexpr float AmbientLight::LightPower(const Vector& position, const Vector& normal) const
{
    return 1.f;
}

constexpr float AmbientLight::SpecularPower(const Vector& position, const Vector& reflectionDirection) const
{
    return 0.f;
}

constexpr Optional<Light::RayForShadow> AmbientLight::RayToPosition(const Vector& position) const
{
    return {};
}
