#pragma once

#include "Material.hpp"

class SimpleColor final : public Material
{
public:
    constexpr SimpleColor(const Color& color)
        : m_surface{color, 0.0, 1.0}
    {
    }
    constexpr SimpleColor(const Color& color, double albedo, double refractiveIndex)
        : m_surface{color, albedo, refractiveIndex}
    {
    }

    constexpr Surface GetSurface(Coord2D uv) const override { return m_surface; }

private:
    const Surface m_surface;
};