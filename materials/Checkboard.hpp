#pragma once

#include "Material.hpp"

class Checkboard final : public Material
{
public:
    constexpr Checkboard(float reflection, const Color& color1, const Color& color2, float tiling)
        : Material(reflection)
        , m_color1(color1)
        , m_color2(color2)
        , m_tiling(tiling)
    {
    }

    constexpr Color GetColor(Coord2D uv) const override
    {
        const bool pairU = IsPairWithTiling(uv.x);
        const bool pairV = IsPairWithTiling(uv.y);
        return (pairU == pairV) ? m_color1 : m_color2;
    }

private:
    constexpr bool IsPairWithTiling(float u) const
    {
        float tiled = u / m_tiling;
        if (tiled < 0)
            tiled = std::abs(tiled) + 1.f;
        return static_cast<int>(tiled) % 2 == 0;
    }

    const Color m_color1;
    const Color m_color2;
    const float m_tiling;
};
