constexpr Raytracer::Raytracer(span<const Object*> objects, span<const Light*> lights)
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
        const Vector reflectionDirection = Vector::reflection(ray.dir, intersection->normal);
        const Material& material = intersection->object->GetMaterial();
        const double albedo = material.GetAlbedo(intersection->uv);
        const double opacity = material.GetOpacity(intersection->uv);
        const double surfaceColorRatio = 1.0 - albedo;
        if (albedo > 0.0)
        {
            // We slightly move the origin to be sure the object won't detect itself.
            const Vector reflectionOrigin = position + reflectionDirection * 0.01;
            const Ray reflectedRay = {reflectionOrigin, reflectionDirection};
            const Color reflectedColor = ProjectRay(reflectedRay);
            pixelColor += reflectedColor * albedo * opacity;
        }

        const Color objectColor = material.GetColor(intersection->uv) * surfaceColorRatio;
        for (const Light* light : m_lights)
        {
            const double lightRatioToPoint = 1.0 - ShadowFromLight(*intersection, light);
            const Color lightColor = light->GetColor();
            const double lightPower = light->LightPower(intersection->position, intersection->normal);
            const double specularPower = light->SpecularPower(position, reflectionDirection);
            pixelColor += objectColor * lightColor * lightRatioToPoint * lightPower * opacity;
            pixelColor += lightColor * lightRatioToPoint * specularPower * opacity;
        }

        const double transparency = 1.0 - opacity;
        if (transparency > 0.0)
        {
            // We slightly move the origin to be sure the object won't detect itself.
            const Vector newRayStart = intersection->position + ray.dir * 0.01;
            const Ray newRay = {newRayStart, ray.dir};
            pixelColor += ProjectRay(newRay) * transparency;
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
        const Optional<double> intersectionDistance = object->IntersectionDistance(rayInRepere);
        if (intersectionDistance)
        {
            const Matrix rotation = object->GetRotation();
            const Vector intersectionInRepere = rayInRepere.AtDistance(*intersectionDistance);
            const Vector intersectionPoint = ray.AtDistance(*intersectionDistance);
            const Vector objectNormal = object->GetNormal(rayInRepere.origin, intersectionInRepere);
            const Vector normal = rotation * objectNormal.Normalized();
            const Coord2D uv = object->GetUV(intersectionInRepere);
            const double distanceSq = (ray.origin - intersectionPoint).LengthSq();
            if (!result || distanceSq < (ray.origin - result->position).LengthSq())
                result = {intersectionPoint, normal, uv, object};
        }
    }
    return result;
}

constexpr double Raytracer::ShadowFromLight(const Intersection& intersection, const Light* light) const
{
    const Optional<Light::RayForShadow> rayForShadow = light->RayToPosition(intersection.position);
    if (!rayForShadow)
        return 0.0;

    return ShadowForRay(rayForShadow->ray, rayForShadow->ray.origin, rayForShadow->maxDistanceSq);
}

constexpr double Raytracer::ShadowForRay(const Ray& ray, const Vector& origin, double maxDistanceSq) const
{
    double shadow = 0.0;
    const Optional<Intersection> lightIntersection = ClosestIntersection(ray);
    if (lightIntersection)
    {
        const double distanceSq = (lightIntersection->position - origin).LengthSq();
        if (distanceSq < maxDistanceSq)
        {
            const Material& objectMaterial = lightIntersection->object->GetMaterial();
            const double objectOpacity = objectMaterial.GetOpacity(lightIntersection->uv);
            const double objectTransparency = 1.0 - objectOpacity;
            shadow = objectOpacity;
            if (objectTransparency > 0.0)
            {
                const Ray newRay = {lightIntersection->position + ray.dir * 0.01, ray.dir};
                shadow += ShadowForRay(newRay, origin, maxDistanceSq) * objectTransparency;
            }
        }
    }
    return shadow;
}
