#pragma once

#include "Sphere.hpp"
#include "SpotLight.hpp"

template <int lightN>
struct Scene
{
    constexpr Scene(const Sphere& object, const std::array<SpotLight, lightN>& lights)
        : object(object)
        , lights(lights)
    {
    }

    Sphere object;
    std::array<SpotLight, lightN> lights;
};
