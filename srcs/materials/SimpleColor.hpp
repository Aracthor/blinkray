#pragma once

#include "Material.hpp"

class SimpleColor final : public Material
{
public:
    constexpr SimpleColor(const Color& color, double albedo)
        : m_color(color)
        , m_albedo(albedo)
    {
    }

    constexpr double GetAlbedo(Coord2D uv) const override { return m_albedo; }
    constexpr Color GetColor(Coord2D uv) const override { return m_color; }

private:
    const Color m_color;
    const double m_albedo;
};