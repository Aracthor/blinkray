#pragma once

struct Vector
{
    float x;
    float y;
    float z;

    constexpr Vector(float x, float y, float z);
    constexpr Vector(const Vector& other);

    constexpr Vector operator+(const Vector& other) const;
    constexpr Vector operator*(float n) const;
    constexpr Vector operator/(float n) const;
};

#include "Vector.ipp"
