constexpr Raytracer::Raytracer(span<const Object*> objects, span<const Light*> lights)
    : m_objects(objects)
    , m_lights(lights)
{
}

constexpr Color Raytracer::ProjectRay(const Ray& ray) const
{
    return ColorForRay(ray, {});
}

constexpr Color Raytracer::ColorForRay(const Ray& ray, const Optional<Intersection>& previousIntersection) const
{
    Color pixelColor = Colors::black;
    const Optional<Intersection> intersection = ClosestIntersection(ray, previousIntersection);
    if (intersection)
    {
        const Vector position = intersection->position;
        const Vector normal = intersection->entering ? intersection->normal : -intersection->normal;
        const Vector reflectionDirection = Vector::reflection(ray.dir, normal);
        const Material::Surface materialSurface = intersection->object->GetMaterial().GetSurface(intersection->uv);
        const double albedo = materialSurface.albedo;
        const double surfaceColorRatio = 1.0 - albedo;
        const Color objectColor = materialSurface.color * surfaceColorRatio;
        const double opacity = objectColor.a;
        if (albedo > 0.0)
        {
            const Ray reflectedRay = {position, reflectionDirection};
            const Color reflectedColor = ColorForRay(reflectedRay, intersection);
            pixelColor += reflectedColor * albedo * opacity;
        }

        for (const Light* light : m_lights)
        {
            const double lightRatioToPoint = 1.0 - ShadowFromLight(intersection->position, light);
            const Color lightColor = light->GetColor();
            const double lightPower = light->LightPower(intersection->position, normal);
            const double specularPower = light->SpecularPower(position, reflectionDirection);
            pixelColor += objectColor * lightColor * lightRatioToPoint * lightPower * opacity;
            pixelColor += lightColor * lightRatioToPoint * specularPower * opacity;
        }

        const double transparency = 1.0 - opacity;
        if (transparency > 0.0)
        {
            const double refractiveRatio =
                intersection->entering ? 1.0 / materialSurface.refractiveIndex : materialSurface.refractiveIndex;
            const Optional<Vector> newRayDir = Vector::refraction(ray.dir, normal, refractiveRatio);
            if (newRayDir)
            {
                const Ray newRay = {intersection->position, *newRayDir};
                pixelColor += ColorForRay(newRay, intersection) * transparency;
            }
        }
    }
    return pixelColor;
}

constexpr Optional<Raytracer::Intersection>
Raytracer::ClosestIntersection(const Ray& ray, const Optional<Intersection>& previousIntersection) const
{
    Optional<Intersection> result;
    for (const Object* object : m_objects)
    {
        const Ray rayInRepere = ray.Transform(object->GetPosition(), object->GetInvertRotation());
        const std::pair<Optional<Vector>, Optional<Vector>> intersections = object->RayIntersection(rayInRepere);
        for (const Optional<Vector>& intersection : {intersections.first, intersections.second})
        {
            if (intersection)
            {
                const Vector intersectionPoint = object->GetRotation() * *intersection + object->GetPosition();
                if (!previousIntersection || previousIntersection->object != object ||
                    (previousIntersection->position - intersectionPoint).LengthSq() > 0.01)
                {
                    const Vector objectNormal = object->GetGeometry().GetNormal(*intersection);
                    const Coord2D uv = object->GetGeometry().GetUV(*intersection);
                    const bool entering = Vector::dot(objectNormal, rayInRepere.origin - *intersection) > 0.0;

                    const Vector normal = object->GetRotation() * objectNormal;
                    const double distanceSq = (ray.origin - intersectionPoint).LengthSq();
                    if (!result || distanceSq < (ray.origin - result->position).LengthSq())
                        result = {intersectionPoint, normal, uv, object, entering};
                }
            }
        }
    }
    return result;
}

constexpr double Raytracer::ShadowFromLight(const Vector& position, const Light* light) const
{
    const Optional<Light::RayForShadow> rayForShadow = light->RayToPosition(position);
    if (!rayForShadow)
        return 0.0;

    return ShadowForRay(rayForShadow->ray, rayForShadow->ray.origin, rayForShadow->maxDistanceSq, {});
}

constexpr double Raytracer::ShadowForRay(const Ray& ray, const Vector& origin, double maxDistanceSq,
                                         const Optional<Intersection>& previousIntersection) const
{
    const Optional<Intersection> lightIntersection = ClosestIntersection(ray, previousIntersection);
    if (!lightIntersection)
        return 0.0;

    const double distanceSq = (lightIntersection->position - origin).LengthSq();
    if (distanceSq >= maxDistanceSq)
        return 0.0;

    const double objectOpacity = lightIntersection->object->GetMaterial().GetSurface(lightIntersection->uv).color.a;
    const double objectTransparency = 1.0 - objectOpacity;
    double shadow = objectOpacity;
    if (objectTransparency > 0.0)
    {
        const Ray newRay = {lightIntersection->position, ray.dir};
        shadow += ShadowForRay(newRay, origin, maxDistanceSq, lightIntersection) * objectTransparency;
    }

    return shadow;
}
