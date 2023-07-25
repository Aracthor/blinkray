#pragma once

#include <array>

#include "Object.hpp"
#include "SpotLight.hpp"
#include "span.hpp"

struct IScene
{
    constexpr virtual span<const Object*> Objects() const = 0;
    constexpr virtual span<const SpotLight> Lights() const = 0;
};

template <std::size_t objectN, std::size_t lightN>
struct Scene final : public IScene
{
    constexpr Scene(const std::array<const Object*, objectN>& objects, const std::array<SpotLight, lightN>& lights)
        : m_objects(objects)
        , m_lights(lights)
    {
    }

    constexpr span<const Object*> Objects() const override
    {
        return span<const Object*>(m_objects.data(), m_objects.size());
    }
    constexpr span<const SpotLight> Lights() const override
    {
        return span<const SpotLight>(m_lights.data(), m_lights.size());
    }

private:
    std::array<const Object*, objectN> m_objects;
    std::array<SpotLight, lightN> m_lights;
};
