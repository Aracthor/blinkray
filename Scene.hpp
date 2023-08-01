#pragma once

#include <array>

#include "Camera.hpp"
#include "Object.hpp"
#include "SpotLight.hpp"
#include "span.hpp"

template <std::size_t objectN, std::size_t lightN>
struct Scene
{
    constexpr Scene(const Camera* camera, const std::array<const Object*, objectN>& objects,
                    const std::array<const SpotLight*, lightN>& lights)
        : m_camera(camera)
        , m_objects(objects)
        , m_lights(lights)
    {
    }

    constexpr const Camera* GetCamera() const { return m_camera; }
    constexpr span<const Object*> Objects() const { return span<const Object*>(m_objects.data(), m_objects.size()); }
    constexpr span<const SpotLight*> Lights() const { return span<const SpotLight*>(m_lights.data(), m_lights.size()); }

private:
    const Camera* m_camera;
    std::array<const Object*, objectN> m_objects;
    std::array<const SpotLight*, lightN> m_lights;
};
