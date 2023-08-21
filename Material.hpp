#pragma once

#include "Color.hpp"
#include "Coord2D.hpp"

class Material
{
public:
    virtual constexpr float GetAlbedo(Coord2D uv) const = 0;
    virtual constexpr Color GetColor(Coord2D uv) const = 0;
};
