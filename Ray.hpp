#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

struct Ray
{
    Vector origin;
    Vector dir;

    constexpr Ray Transform(const Vector& position, const Matrix& invertRotation) const;

    constexpr Vector AtDistance(float distance) const;
};

#include "Ray.ipp"
