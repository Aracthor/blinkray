#pragma once

#include "Color.hpp"
#include "Coord2D.hpp"

class Material
{
public:
    virtual Color GetColor(Coord2D uv) const = 0;
};
