#pragma once

#include <utility> // std::pair

#include "Optional.hpp"

namespace Quadratic
{
constexpr int solve(float a, float b, float c, float& result1, float& result2);
constexpr std::pair<Optional<float>, Optional<float>> sortedPositiveResults(float a, float b, float c);
} // namespace Quadratic

#include "Quadratic.ipp"

static_assert(*Quadratic::sortedPositiveResults(3, -4, 1).first == 1.f / 3.f);
static_assert(*Quadratic::sortedPositiveResults(-2, 3, 2).first == 2.f);
