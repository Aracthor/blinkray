#pragma once

#include "Vector.hpp"

struct Ray
{
    Vector origin;
    Vector dir;

    constexpr Ray Transform(const Vector& translation) const;

    constexpr Vector AtDistance(float distance) const;
};

#include "Ray.ipp"
