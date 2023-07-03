#pragma once

#include <array>

#include "Sphere.hpp"
#include "SpotLight.hpp"

template <int objectN, int lightN>
struct Scene
{
    constexpr Scene(const std::array<Sphere, objectN>& objects,
                    const std::array<SpotLight, lightN>& lights)
        : objects(objects)
        , lights(lights)
    {
    }

    std::array<Sphere, objectN> objects;
    std::array<SpotLight, lightN> lights;
};
