#pragma once

#include "Image.hpp"
#include "Material.hpp"

template <int WIDTH, int HEIGHT>
class Textured final : public Material
{
public:
    constexpr Textured(const Image<WIDTH, HEIGHT>& color, double tiling, double albedo, double refractiveIndex)
        : m_color(color)
        , m_tiling(tiling)
        , m_albedo(albedo)
        , m_refractiveIndex(refractiveIndex)
    {
    }

    constexpr Surface GetSurface(Coord2D uv) const override
    {
        const Coord2D textureCoords = this->GetTextureUV(uv);
        const Color color = m_color.GetPixel(textureCoords.x, textureCoords.y);
        return {color, m_albedo, m_refractiveIndex};
    }

private:
    constexpr double Tile(double value, double n) const
    {
        double t = value / m_tiling;
        t -= (int)t;
        if (t < 0.f)
            t += 1;
        return t * n;
    }

    constexpr Coord2D GetTextureUV(Coord2D uv) const { return Coord2D{Tile(uv.x, WIDTH), Tile(uv.y, HEIGHT)}; }

    const Image<WIDTH, HEIGHT>& m_color;
    double m_tiling;
    double m_albedo;
    double m_refractiveIndex;
};
