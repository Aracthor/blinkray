#include "Maths.hpp"

namespace Quadratic
{
constexpr int solve(float a, float b, float c, float& result1, float& result2)
{
    const float d = b * b - 4 * a * c;
    if (d < 0)
        return 0;
    if (d == 0)
    {
        result1 = -b / (2 * a);
        return 1;
    }
    const float dRoot = Maths::sqrt(d);
    result1 = (-b + dRoot) / (2 * a);
    result2 = (-b - dRoot) / (2 * a);
    return 2;
}

constexpr Optional<float> shortestPositiveResult(float a, float b, float c)
{
    float result1 = 0.f, result2 = 0.f;
    const int intersectionCount = solve(a, b, c, result1, result2);
    if (intersectionCount == 0)
        return {};
    if (intersectionCount == 1)
        return (result1 > 0.f) ? result1 : Optional<Vector>();

    if (result1 < 0.f && result2 < 0.f)
        return {};
    if (result1 < 0.f)
        return result2;
    if (result2 < 0.f)
        return result1;
    return std::min(result1, result2);
}
} // namespace Quadratic