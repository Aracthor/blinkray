#pragma once

#include "Color.hpp"

class Material
{
public:
    virtual constexpr Color GetColor() const = 0;
};
