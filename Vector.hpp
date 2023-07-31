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
    constexpr Vector Normalized() const;

    constexpr Vector operator-() const;
    constexpr Vector operator+(const Vector& other) const;
    constexpr Vector operator-(const Vector& other) const;
    constexpr Vector operator*(float n) const;
    constexpr Vector operator/(float n) const;

    constexpr static float dot(const Vector& u, const Vector& v);
    constexpr static Vector reflection(const Vector& dir, const Vector& normal);
};

#include "Vector.ipp"

static_assert(Vector(3.f, 4.f, 0.f).Length() == 5.f);