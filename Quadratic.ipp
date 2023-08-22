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

constexpr std::pair<Optional<float>, Optional<float>> sortedPositiveResults(float a, float b, float c)
{
    float result1 = 0.f, result2 = 0.f;
    const int intersectionCount = solve(a, b, c, result1, result2);
    if (intersectionCount == 0)
        return {};
    if (intersectionCount == 1)
    {
        if (result1 < 0.f)
            return {};
        return {Optional<float>(result1), {}};
    }

    if (result1 < 0.f && result2 < 0.f)
        return {};
    if (result1 < 0.f)
        return {Optional<float>(result2), {}};
    if (result2 < 0.f)
        return {Optional<float>(result1), {}};
    if (result1 > result2)
        std::swap(result1, result2);
    return {Optional<float>(result1), Optional<float>(result2)};
}
} // namespace Quadratic