#pragma once

#include "Material.hpp"

class Checkboard final : public Material
{
public:
    constexpr Checkboard(const Material* material1, const Material* material2, float tiling)
        : m_material1(material1)
        , m_material2(material2)
        , m_tiling(tiling)
    {
    }

    constexpr float GetAlbedo(Coord2D uv) const override { return GetMaterialFromUV(uv)->GetAlbedo(uv); }
    constexpr float GetOpacity(Coord2D uv) const override { return GetMaterialFromUV(uv)->GetOpacity(uv); }
    constexpr Color GetColor(Coord2D uv) const override { return GetMaterialFromUV(uv)->GetColor(uv); }

private:
    constexpr bool IsPairWithTiling(float u) const
    {
        float tiled = u / m_tiling;
        if (tiled < 0)
            tiled = std::abs(tiled) + 1.f;
        return static_cast<int>(tiled) % 2 == 0;
    }

    constexpr const Material* GetMaterialFromUV(Coord2D uv) const
    {
        const bool pairU = IsPairWithTiling(uv.x);
        const bool pairV = IsPairWithTiling(uv.y);
        return (pairU == pairV) ? m_material1 : m_material2;
    }

    const Material* m_material1;
    const Material* m_material2;
    const float m_tiling;
};
