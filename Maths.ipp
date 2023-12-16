namespace Maths
{
constexpr double abs(double number)
{
    return number < 0.0 ? -number : number;
}

constexpr double pow(double number, int n)
{
    double result = 1.0;

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
constexpr double sqrt(double n)
{
    double result = n;
    double previous = 0.0;
    while (result != previous)
    {
        previous = result;
        result = (result + n / result) / 2.0;
    }
    return result;
}

constexpr double degToRad(double angle)
{
    return angle * _PI / 180.0;
}

constexpr double cos(double angle)
{
    return (sin(angle + _PI_2));
}

// Taylor's polynomial theorem with 5 iterations.
// https://en.wikipedia.org/wiki/Taylor_series#Approximation_error_and_convergence
constexpr double sin(double angle)
{
    // set x between _PI and -_PI.
    while (angle < -_PI)
        angle += _2_PI;
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

constexpr double acos(double number)
{
    return (_PI_2 - asin(number));
}

// Will only work with number between -1 and 1 !
// Here we use it only for UV functions.
// Quite imprecise for number close of -1 or 1.
constexpr double asin(double number)
{
    // clang-format off
    return (number
            + pow(number, 3) * 1.0 / 6.0
            + pow(number, 5) * 3.0 / 40.0
            + pow(number, 7) * 5.0 / 112.0
            + pow(number, 9) * 35.0 / 1152.0
            + pow(number, 11) * 63.0 / 2816.0
            );
    // clang-format on
}
} // namespace Maths
