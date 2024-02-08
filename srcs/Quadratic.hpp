#pragma once

#include <utility> // std::pair

#include "Optional.hpp"

namespace Quadratic
{
constexpr int solve(double a, double b, double c, double& result1, double& result2);
constexpr std::pair<Optional<double>, Optional<double>> sortedPositiveResults(double a, double b, double c);
} // namespace Quadratic

#include "Quadratic.ipp"

static_assert(*Quadratic::sortedPositiveResults(3, -4, 1).first == 1.0 / 3.0);
static_assert(*Quadratic::sortedPositiveResults(-2, 3, 2).first == 2.0);
