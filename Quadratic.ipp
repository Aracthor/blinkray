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
        result1 = -b / 2 * a;
        return 1;
    }
    const float dRoot = Maths::sqrt(d);
    result1 = (-b + dRoot) / 2 * a;
    result2 = (-b - dRoot) / 2 * a;
    return 2;
}
} // namespace Quadratic