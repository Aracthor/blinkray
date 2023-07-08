#pragma once

#include "Optional.hpp"

namespace Quadratic
{
constexpr int solve(float a, float b, float c, float& result1, float& result2);
constexpr Optional<float> shortestPositiveResult(float a, float b, float c);
} // namespace Quadratic

#include "Quadratic.ipp"

static_assert(*Quadratic::shortestPositiveResult(3, -4, 1) == 1.f / 3.f);
static_assert(*Quadratic::shortestPositiveResult(-2, 3, 2) == 2.f);
