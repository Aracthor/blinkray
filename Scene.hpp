#pragma once

#include <array>

#include "Object.hpp"
#include "SpotLight.hpp"

template <std::size_t objectN, std::size_t lightN>
struct Scene
{
    constexpr Scene(const std::array<const Object*, objectN>& objects,
                    const std::array<SpotLight, lightN>& lights)
        : objects(objects)
        , lights(lights)
    {
    }

    std::array<const Object*, objectN> objects;
    std::array<SpotLight, lightN> lights;
};
