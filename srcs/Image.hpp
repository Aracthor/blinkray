#pragma once

#include "Color.hpp"

template <int WIDTH, int HEIGHT>
class Image
{
public:
    constexpr auto ToBitmapFile() const;

    constexpr Color GetPixel(int x, int y) const { return m_pixels[WIDTH * y + x]; }
    constexpr void SetPixel(int x, int y, Color color) { m_pixels[WIDTH * y + x] = color; }

private:
    Color m_pixels[WIDTH * HEIGHT];
};

template <const uint8_t* DATA>
constexpr static auto ImageFromBitmapFile();

#include "Image.ipp"