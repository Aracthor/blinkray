namespace Maths
{
constexpr float abs(float number)
{
    return number < 0.f ? -number : number;
}

constexpr float pow(float number, int n)
{
    float result = 1.f;

    while (n > 0)
    {
        result *= number;
        n--;
    }

    return result;
}

constexpr int fact(int n)
{
    int i = n;

    while (i > 1)
    {
        n *= i - 1;
        i--;
    }
    return n;
}

// Newton-Raphson method.
// https://en.wikipedia.org/wiki/Newton's_method
constexpr float sqrt(float n)
{
    float result = n;
    float previous = 0.f;
    while (result != previous)
    {
        previous = result;
        result = (result + n / result) / 2.f;
    }
    return result;
}

constexpr float degToRad(float angle)
{
    return angle * _PI / 180.f;
}

constexpr float cos(float angle)
{
    return (sin(angle + _PI_2));
}

// Taylor's polynomial theorem with 4 iterations.
// https://en.wikipedia.org/wiki/Taylor_series#Approximation_error_and_convergence
constexpr float sin(float angle)
{
    // set x between _PI and -_PI.
    if (angle < 0.0f)
        angle = -angle;
    while (angle > _PI)
        angle -= _2_PI;

    // clang-format off
    return (angle
            - pow(angle, 3) / fact(3)
            + pow(angle, 5) / fact(5)
            - pow(angle, 7) / fact(7)
            + pow(angle, 9) / fact(9)
            - pow(angle, 11) / fact(11)
            );
    // clang-format on
}
} // namespace Maths
