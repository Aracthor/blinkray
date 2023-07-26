#include <algorithm>

constexpr Color& Color::operator+=(const Color& other)
{
    r = std::min(r + other.r, 1.f);
    g = std::min(g + other.g, 1.f);
    b = std::min(b + other.b, 1.f);
    return *this;
}

constexpr Color Color::operator*(const Color& other) const
{
    return Color(r * other.r, g * other.g, b * other.b, a * other.a);
}

constexpr Color Color::operator*(float n) const
{
    n = std::min(1.f, n);
    return Color(r * n, g * n, b * n, a);
}