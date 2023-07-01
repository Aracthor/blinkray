namespace Maths
{
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
} // namespace Maths
