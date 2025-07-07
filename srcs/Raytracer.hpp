#pragma once

#include "Color.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "span.hpp"

class Raytracer
{
public:
    constexpr Raytracer(span<const Object*> objects, span<const Light*> lights);

    constexpr Color ProjectRay(const Ray& ray) const;

private:
    struct Intersection
    {
        Vector position;
        Vector normal;
        Coord2D uv;
        const Object* object;
        bool entering;
    };

    constexpr Color ColorForRay(const Ray& ray, const Optional<Intersection>& previousIntersection) const;

    constexpr double ShadowFromLight(const Vector& position, const Light* light) const;
    constexpr double ShadowForRay(const Ray& ray, const Vector& origin, double maxDistanceSq,
                                  const Optional<Intersection>& previousIntersection) const;

    constexpr Optional<Intersection> ClosestIntersection(const Ray& ray,
                                                         const Optional<Intersection>& previousIntersection) const;

    span<const Object*> m_objects;
    span<const Light*> m_lights;
};

#include "Raytracer.ipp"
