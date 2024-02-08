#pragma once

#include <array>

#include "Camera.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "span.hpp"

template <std::size_t objectN, std::size_t lightN>
struct Scene
{
    constexpr Scene(const Camera* camera, const std::array<const Object*, objectN>& objects,
                    const std::array<const Light*, lightN>& lights)
        : m_camera(camera)
        , m_objects(objects)
        , m_lights(lights)
    {
    }

    constexpr const Camera* GetCamera() const { return m_camera; }
    constexpr span<const Object*> Objects() const { return span<const Object*>(m_objects.data(), m_objects.size()); }
    constexpr span<const Light*> Lights() const { return span<const Light*>(m_lights.data(), m_lights.size()); }

private:
    const Camera* m_camera;
    std::array<const Object*, objectN> m_objects;
    std::array<const Light*, lightN> m_lights;
};
