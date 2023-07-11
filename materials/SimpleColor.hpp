#pragma once

#include "Material.hpp"

class SimpleColor final : public Material
{
public:
    constexpr SimpleColor(float reflection, const Color& color)
        : Material(reflection)
        , m_color(color)
    {
    }

    constexpr Color GetColor(Coord2D uv) const override { return m_color; }

private:
    const Color m_color;
};