#pragma once

#include "Color.hpp"
#include "Coord2D.hpp"

class Material
{
public:
    constexpr Material(float albedo)
        : m_albedo(albedo)
    {
    }

    constexpr float GetAlbedo() const { return m_albedo; }

    virtual constexpr Color GetColor(Coord2D uv) const = 0;

private:
    const float m_albedo;
};
