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
        const Vector position = intersection->position;
        const Vector dir = ray.dir;
        const Vector normal = intersection->normal;
        const Vector reflectionDirection = dir - normal * 2 * Vector::dot(dir, normal);
        const Material& material = intersection->object->GetMaterial();
        const float reflectionRatio = material.GetReflection();
        const float surfaceColorRatio = 1.f - reflectionRatio;
        if (reflectionRatio > 0.f)
        {
            // We slightly move the origin to be sure the object won't detect itself.
            const Vector reflectionOrigin = position + reflectionDirection * 0.01;
            const Ray reflectedRay = {reflectionOrigin, reflectionDirection};
            const Color reflectedColor = ProjectRay(reflectedRay);
            pixelColor += reflectedColor * reflectionRatio;
        }
        if (surfaceColorRatio > 0.f)
        {
            const Color objectColor = material.GetColor(intersection->uv) * surfaceColorRatio;
            const Color specularColor = Colors::white * surfaceColorRatio;
            for (const SpotLight& light : m_lights)
            {
                const float lightPower = LightPowerOnPoint(*intersection, light);
                const float specularPower = light.SpecularPower(position, reflectionDirection);
                pixelColor += objectColor * lightPower;
                pixelColor += specularColor * specularPower;
            }
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
            const Vector normal = rotation * objectNormal.Normalized();
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
