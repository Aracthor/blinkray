constexpr Raytracer::Raytracer(span<const Object*> objects, span<const SpotLight> lights)
    : m_objects(objects)
    , m_lights(lights)
{
}

constexpr Color Raytracer::ProjectRay(const Ray& ray) const
{
    Color pixelColor = Colors::black;
    const Optional<Intersection> intersection = ClosestIntersection(ray);
    if (intersection)
    {
        const Material& material = intersection->object->GetMaterial();
        const Color objectColor = material.GetColor(intersection->uv);
        for (const SpotLight& light : m_lights)
        {
            pixelColor += objectColor * LightPowerOnPoint(*intersection, light);
        }
    }
    return pixelColor;
}

constexpr Optional<Raytracer::Intersection> Raytracer::ClosestIntersection(const Ray& ray) const
{
    Optional<Intersection> result;
    for (const Object* object : m_objects)
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

constexpr float Raytracer::LightPowerOnPoint(const Intersection& intersection,
                                             const SpotLight& light) const
{
    const Ray lightRay = light.RayToPosition(intersection.position);
    const Optional<Intersection> lightIntersection = ClosestIntersection(lightRay);
    if (lightIntersection && lightIntersection->object == intersection.object)
    {
        return light.LightPower(intersection.position, intersection.normal);
    }
    return 0.f;
}
