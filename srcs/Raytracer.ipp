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
        const Material::Surface materialSurface = intersection->material->GetSurface(intersection->uv);
        const double albedo = materialSurface.albedo;
        const double surfaceColorRatio = 1.0 - albedo;
        const Color objectColor = materialSurface.color * surfaceColorRatio;
        const double opacity = objectColor.a;
        if (albedo > 0.0)
        {
            // We slightly move the origin to be sure the object won't detect itself.
            const Vector reflectionOrigin = position + reflectionDirection * 0.01;
            const Ray reflectedRay = {reflectionOrigin, reflectionDirection};
            const Color reflectedColor = ProjectRay(reflectedRay);
            pixelColor += reflectedColor * albedo * opacity;
        }

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
            const double refractiveRatio = 1.0 / materialSurface.refractiveIndex;
            const Optional<Vector> newRayDir = Vector::refraction(ray.dir, intersection->normal, refractiveRatio);
            if (newRayDir)
            {
                // We slightly move the origin to be sure the object won't detect itself.
                const Vector newRayStart = intersection->position + ray.dir * 0.01;
                const Ray newRay = {newRayStart, *newRayDir};
                pixelColor += ProjectRay(newRay) * transparency;
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
        const Optional<Object::Intersection> intersection = object->RayIntersection(rayInRepere);
        if (intersection)
        {
            const Vector intersectionPoint = object->GetRotation() * intersection->position + object->GetPosition();
            const Vector normal = object->GetRotation() * intersection->normal;
            const double distanceSq = (ray.origin - intersectionPoint).LengthSq();
            if (!result || distanceSq < (ray.origin - result->position).LengthSq())
                result = {intersectionPoint, normal, intersection->uv, &object->GetMaterial()};
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
            const double objectOpacity = lightIntersection->material->GetSurface(lightIntersection->uv).color.a;
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
