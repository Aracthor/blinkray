#pragma once

#include "Color.hpp"

template <int WIDTH, int HEIGHT>
class Image
{
public:
    constexpr auto ToBitmapFile() const;

    constexpr void SetPixel(int x, int y, Color color) { m_pixels[WIDTH * y + x] = color; }

private:
    Color m_pixels[WIDTH * HEIGHT];
};

#include "Image.ipp"