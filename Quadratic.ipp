#include "Maths.hpp"

namespace Quadratic
{
constexpr int solve(double a, double b, double c, double& result1, double& result2)
{
    const double d = b * b - 4 * a * c;
    if (d < 0)
        return 0;
    if (d == 0)
    {
        result1 = -b / (2 * a);
        return 1;
    }
    const double dRoot = Maths::sqrt(d);
    result1 = (-b + dRoot) / (2 * a);
    result2 = (-b - dRoot) / (2 * a);
    return 2;
}

constexpr std::pair<Optional<double>, Optional<double>> sortedPositiveResults(double a, double b, double c)
{
    double result1 = 0.0, result2 = 0.0;
    const int intersectionCount = solve(a, b, c, result1, result2);
    if (intersectionCount == 0)
        return {};
    if (intersectionCount == 1)
    {
        if (result1 < 0.0)
            return {};
        return {Optional<double>(result1), {}};
    }

    if (result1 < 0.0 && result2 < 0.0)
        return {};
    if (result1 < 0.0)
        return {Optional<double>(result2), {}};
    if (result2 < 0.0)
        return {Optional<double>(result1), {}};
    if (result1 > result2)
        std::swap(result1, result2);
    return {Optional<double>(result1), Optional<double>(result2)};
}
} // namespace Quadratic