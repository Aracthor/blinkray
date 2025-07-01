#pragma once

struct Vector
{
    double x;
    double y;
    double z;

    constexpr Vector();
    constexpr Vector(double x, double y, double z);
    constexpr Vector(const Vector& other);

    constexpr double LengthSq() const;
    constexpr double Length() const;
    constexpr Vector Normalized() const;

    constexpr Vector xy0() const;

    constexpr Vector operator-() const;
    constexpr Vector operator+(const Vector& other) const;
    constexpr Vector operator-(const Vector& other) const;
    constexpr Vector operator*(double n) const;
    constexpr Vector operator/(double n) const;

    constexpr static double dot(const Vector& u, const Vector& v);
    constexpr static Vector reflection(const Vector& dir, const Vector& normal);
};

#include "Vector.ipp"

static_assert(Vector(3.0, 4.0, 0.0).Length() == 5.0);