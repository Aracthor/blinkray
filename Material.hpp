#pragma once

#include "Color.hpp"
#include "Coord2D.hpp"

class Material
{
public:
    virtual constexpr double GetAlbedo(Coord2D uv) const = 0;
    virtual constexpr double GetOpacity(Coord2D uv) const = 0;
    virtual constexpr Color GetColor(Coord2D uv) const = 0;
};
