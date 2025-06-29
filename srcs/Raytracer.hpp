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
        Vector position{};
        Vector normal{};
        Coord2D uv{};
        const Material* material{};
    };

    constexpr double ShadowFromLight(const Intersection& intersection, const Light* light) const;
    constexpr double ShadowForRay(const Ray& ray, const Vector& origin, double maxDistanceSq) const;

    constexpr Optional<Intersection> ClosestIntersection(const Ray& ray) const;

    span<const Object*> m_objects;
    span<const Light*> m_lights;
};

#include "Raytracer.ipp"
