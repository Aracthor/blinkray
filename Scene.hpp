#pragma once

#include <array>

#include "Camera.hpp"
#include "Object.hpp"
#include "SpotLight.hpp"
#include "span.hpp"

struct IScene
{
    constexpr virtual const Camera* GetCamera() const = 0;
    constexpr virtual span<const Object*> Objects() const = 0;
    constexpr virtual span<const SpotLight*> Lights() const = 0;
};

template <std::size_t objectN, std::size_t lightN>
struct Scene final : public IScene
{
    constexpr Scene(const Camera* camera, const std::array<const Object*, objectN>& objects,
                    const std::array<const SpotLight*, lightN>& lights)
        : m_camera(camera)
        , m_objects(objects)
        , m_lights(lights)
    {
    }

    constexpr const Camera* GetCamera() const override { return m_camera; }
    constexpr span<const Object*> Objects() const override
    {
        return span<const Object*>(m_objects.data(), m_objects.size());
    }
    constexpr span<const SpotLight*> Lights() const override
    {
        return span<const SpotLight*>(m_lights.data(), m_lights.size());
    }

private:
    const Camera* m_camera;
    std::array<const Object*, objectN> m_objects;
    std::array<const SpotLight*, lightN> m_lights;
};
