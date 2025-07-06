#pragma once

#include "Color.hpp"
#include "Coord2D.hpp"

class Material
{
public:
    struct Surface
    {
        Color color;
        double albedo;
        double refractiveIndex;
    };

    virtual constexpr Surface GetSurface(Coord2D uv) const = 0;
};
