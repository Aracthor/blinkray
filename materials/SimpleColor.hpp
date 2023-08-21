#pragma once

#include "Material.hpp"

class SimpleColor final : public Material
{
public:
    constexpr SimpleColor(float albedo, float opacity, const Color& color)
        : m_albedo(albedo)
        , m_opacity(opacity)
        , m_color(color)
    {
    }

    constexpr float GetAlbedo(Coord2D uv) const override { return m_albedo; }
    constexpr float GetOpacity(Coord2D uv) const override { return m_opacity; }
    constexpr Color GetColor(Coord2D uv) const override { return m_color; }

private:
    const float m_albedo;
    const float m_opacity;
    const Color m_color;
};