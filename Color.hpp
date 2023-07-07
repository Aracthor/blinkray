#pragma once

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    constexpr Color()
        : r(0)
        , g(0)
        , b(0)
        , a(0)
    {
    }

    constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }

    constexpr Color& operator+=(const Color& other);

    constexpr Color operator*(float n) const;
};

namespace Colors
{
constexpr Color red = Color(0xFF, 0x00, 0x00, 0xFF);
constexpr Color green = Color(0x00, 0xFF, 0x00, 0xFF);
constexpr Color blue = Color(0x00, 0x00, 0xFF, 0xFF);
constexpr Color white = Color(0xFF, 0xFF, 0xFF, 0xFF);
constexpr Color black = Color(0x00, 0x00, 0x00, 0xFF);
} // namespace Colors

#include "Color.ipp"
