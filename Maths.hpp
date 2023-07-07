#pragma once

namespace Maths
{
constexpr float sqrt(float n);
} // namespace Maths

#include "Maths.ipp"

static_assert(Maths::sqrt(1.f) == 1.f);
static_assert(Maths::sqrt(4.f) == 2.f);
static_assert(Maths::sqrt(100.f) == 10.f);