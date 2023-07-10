#pragma once

#include "Color.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "Scene.hpp"

struct Intersection
{
    Vector position{};
    Vector normal{};
    Coord2D uv{};
    const Object* object{};
};

template <std::size_t objectN, std::size_t lightN>
class Raytracer
{
public:
    constexpr Raytracer(const Scene<objectN, lightN>& scene);

    constexpr Color ProjectRay(const Ray& ray) const;

private:
    constexpr void ApplyLightIfPracticable(const Intersection& intersection,
                                           const Color& objectColor, const SpotLight& light,
                                           Color& pixelColor) const;

    constexpr Optional<Intersection> ClosestIntersection(const Ray& ray) const;

    const Scene<objectN, lightN>& m_scene;
};

#include "Raytracer.ipp"
