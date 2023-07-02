#include <algorithm>

namespace
{
constexpr unsigned char addWithoutOverflow(unsigned char a, unsigned char b)
{
    const int sum = static_cast<int>(a) + static_cast<int>(b);
    constexpr unsigned char max = std::numeric_limits<unsigned char>::max();
    return sum > max ? max : sum;
}
} // namespace

constexpr Color& Color::operator+=(const Color& other)
{
    r = addWithoutOverflow(r, other.r);
    g = addWithoutOverflow(g, other.g);
    b = addWithoutOverflow(b, other.b);
    return *this;
}

constexpr Color Color::operator*(float n) const
{
    n = std::min(1.f, n);
    return Color(r * n, g * n, b * n, a);
}