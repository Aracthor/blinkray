#pragma once

#include "Material.hpp"

class SimpleColor final : public Material
{
public:
    constexpr SimpleColor(double albedo, double opacity, const Color& color)
        : m_albedo(albedo)
        , m_opacity(opacity)
        , m_color(color)
    {
    }

    constexpr double GetAlbedo(Coord2D uv) const override { return m_albedo; }
    constexpr double GetOpacity(Coord2D uv) const override { return m_opacity; }
    constexpr Color GetColor(Coord2D uv) const override { return m_color; }

private:
    const double m_albedo;
    const double m_opacity;
    const Color m_color;
};