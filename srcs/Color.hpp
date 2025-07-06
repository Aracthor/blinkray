#pragma once

struct Color
{
    double r;
    double g;
    double b;
    double a;

    constexpr Color()
        : r(0)
        , g(0)
        , b(0)
        , a(0)
    {
    }

    constexpr Color(double r, double g, double b, double a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }

    constexpr Color& operator+=(const Color& other);
    constexpr Color operator*(const Color& other) const;

    constexpr Color operator*(double n) const;
};

namespace Colors
{
constexpr Color red = Color(1.0, 0.0, 0.0, 1.0);
constexpr Color green = Color(0.0, 1.0, 0.0, 1.0);
constexpr Color blue = Color(0.0, 0.0, 1.0, 1.0);
constexpr Color yellow = Color(1.0, 1.0, 0.0, 1.0);
constexpr Color white = Color(1.0, 1.0, 1.0, 1.0);
constexpr Color black = Color(0.0, 0.0, 0.0, 1.0);
constexpr Color transparent = Color(0.0, 0.0, 0.0, 0.0);
} // namespace Colors

#include "Color.ipp"
