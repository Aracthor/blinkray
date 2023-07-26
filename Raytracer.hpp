#pragma once

#include "Color.hpp"
#include "Object.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "SpotLight.hpp"
#include "span.hpp"

class Raytracer
{
public:
    constexpr Raytracer(span<const Object*> objects, span<const SpotLight*> lights);

    constexpr Color ProjectRay(const Ray& ray) const;

private:
    struct Intersection
    {
        Vector position{};
        Vector normal{};
        Coord2D uv{};
        const Object* object{};
    };

    constexpr float LightPowerOnPoint(const Intersection& intersection, const SpotLight* light) const;

    constexpr Optional<Intersection> ClosestIntersection(const Ray& ray) const;

    span<const Object*> m_objects;
    span<const SpotLight*> m_lights;
};

#include "Raytracer.ipp"
