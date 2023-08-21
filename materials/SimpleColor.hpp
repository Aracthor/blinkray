#pragma once

#include "Material.hpp"

class SimpleColor final : public Material
{
public:
    constexpr SimpleColor(float albedo, const Color& color)
        : m_albedo(albedo)
        , m_color(color)
    {
    }

    constexpr float GetAlbedo(Coord2D uv) const override { return m_albedo; }

    constexpr Color GetColor(Coord2D uv) const override { return m_color; }

private:
    const float m_albedo;
    const Color m_color;
};