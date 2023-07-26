#pragma once

struct Color
{
    float r;
    float g;
    float b;
    float a;

    constexpr Color()
        : r(0)
        , g(0)
        , b(0)
        , a(0)
    {
    }

    constexpr Color(float r, float g, float b, float a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }

    constexpr Color& operator+=(const Color& other);
    constexpr Color operator*(const Color& other) const;

    constexpr Color operator*(float n) const;
};

namespace Colors
{
constexpr Color red = Color(1.f, 0.f, 0.f, 1.f);
constexpr Color green = Color(0.f, 1.f, 0.f, 1.f);
constexpr Color blue = Color(0.f, 0.f, 1.f, 1.f);
constexpr Color yellow = Color(1.f, 1.f, 0.f, 1.f);
constexpr Color white = Color(1.f, 1.f, 1.f, 1.f);
constexpr Color black = Color(0.f, 0.f, 0.f, 1.f);
} // namespace Colors

#include "Color.ipp"
