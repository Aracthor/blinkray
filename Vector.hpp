#pragma once

struct Vector
{
    float x;
    float y;
    float z;

    constexpr Vector();
    constexpr Vector(float x, float y, float z);
    constexpr Vector(const Vector& other);

    constexpr float LengthSq() const;
    constexpr float Length() const;

    constexpr Vector operator+(const Vector& other) const;
    constexpr Vector operator-(const Vector& other) const;
    constexpr Vector operator*(float n) const;
    constexpr Vector operator/(float n) const;

    constexpr static float dot(const Vector& u, const Vector& v);
};

#include "Vector.ipp"
