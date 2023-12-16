#include <algorithm>

constexpr Color& Color::operator+=(const Color& other)
{
    r = std::min(r + other.r, 1.0);
    g = std::min(g + other.g, 1.0);
    b = std::min(b + other.b, 1.0);
    return *this;
}

constexpr Color Color::operator*(const Color& other) const
{
    return Color(r * other.r, g * other.g, b * other.b, a * other.a);
}

constexpr Color Color::operator*(double n) const
{
    n = std::min(1.0, n);
    return Color(r * n, g * n, b * n, a);
}