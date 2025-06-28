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

// Maclaurin's series
// https://en.wikipedia.org/wiki/Taylor_series#Approximation_error_and_convergence
template <int N>
constexpr double sin_taylor_polynomial(double angle)
{
    static_assert(N > 0);
    constexpr int p = N * 2 + 1;
    constexpr int sign = pow(-1, N);
    const double iteration = sign * pow(angle, p) / fact(p);
    return iteration + sin_taylor_polynomial<N - 1>(angle);
}

template <>
constexpr double sin_taylor_polynomial<0>(double angle)
{
    return angle;
}

constexpr double sin(double angle)
{
    while (angle < -_PI)
        angle += _2_PI;
    while (angle > _PI)
        angle -= _2_PI;

    return sin_taylor_polynomial<5>(angle);
}

constexpr double acos(double number)
{
    return (_PI_2 - asin(number));
}

template <int N>
constexpr double asin_taylor_polynomial(double angle)
{
    static_assert(N > 0);
    constexpr int p = 2 * N + 1;
    const double iteration = fact(2 * N) / (pow(4, N) * pow(fact(N), 2) * p) * pow(angle, p);
    return iteration + asin_taylor_polynomial<N - 1>(angle);
}

template <>
constexpr double asin_taylor_polynomial<0>(double angle)
{
    return angle;
}

// Will only work with number between -1 and 1 !
// Here we use it only for UV functions.
// Quite imprecise for number close of -1 or 1.
constexpr double asin(double number)
{
    return asin_taylor_polynomial<5>(number);
}
} // namespace Maths
