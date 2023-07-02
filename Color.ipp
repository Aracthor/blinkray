#include <algorithm>

constexpr Color Color::operator*(float n) const
{
    n = std::min(1.f, n);
    return Color(r * n, g * n, b * n, a);
}