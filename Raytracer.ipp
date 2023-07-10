template <std::size_t objectN, std::size_t lightN>
constexpr Raytracer<objectN, lightN>::Raytracer(const Scene<objectN, lightN>& scene)
    : m_scene(scene)
{
}

template <std::size_t objectN, std::size_t lightN>
constexpr Color Raytracer<objectN, lightN>::ProjectRay(const Ray& ray) const
{
    Color pixelColor = Colors::black;
    const Optional<Intersection> intersection = ClosestIntersection(ray);
    if (intersection)
    {
        const Color objectColor = intersection->object->GetMaterial().GetColor(intersection->uv);
        for (const SpotLight& light : m_scene.lights)
        {
            ApplyLightIfPracticable(*intersection, objectColor, light, pixelColor);
        }
    }
    return pixelColor;
}

template <std::size_t objectN, std::size_t lightN>
constexpr Optional<Intersection>
Raytracer<objectN, lightN>::ClosestIntersection(const Ray& ray) const
{
    Optional<Intersection> result;
    for (const Object* object : m_scene.objects)
    {
        const Ray rayInRepere = ray.Transform(object->GetPosition(), object->GetInvertRotation());
        const Optional<float> intersectionDistance = object->IntersectionDistance(rayInRepere);
        if (intersectionDistance)
        {
            const Matrix rotation = object->GetRotation();
            const Vector intersectionInRepere = rayInRepere.AtDistance(*intersectionDistance);
            const Vector intersectionPoint = ray.AtDistance(*intersectionDistance);
            const Vector objectNormal = object->GetNormal(rayInRepere.origin, intersectionInRepere);
            const Vector normal = rotation * objectNormal;
            const Coord2D uv = object->GetUV(intersectionInRepere);
            const float distanceSq = (ray.origin - intersectionPoint).LengthSq();
            if (!result || distanceSq < (ray.origin - result->position).LengthSq())
                result = {intersectionPoint, normal, uv, object};
        }
    }
    return result;
}

template <std::size_t objectN, std::size_t lightN>
constexpr void Raytracer<objectN, lightN>::ApplyLightIfPracticable(const Intersection& intersection,
                                                                   const Color& objectColor,
                                                                   const SpotLight& light,
                                                                   Color& pixelColor) const
{
    const Ray lightRay = light.RayToPosition(intersection.position);
    const Optional<Intersection> lightIntersection = ClosestIntersection(lightRay);
    if (lightIntersection && lightIntersection->object == intersection.object)
    {
        const float lightPower = light.LightPower(intersection.position, intersection.normal);
        pixelColor += objectColor * lightPower;
    }
}
