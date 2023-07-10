#pragma once

namespace Maths
{
constexpr float _PI = 3.14159265359;
constexpr float _PI_2 = _PI / 2.f;
constexpr float _2_PI = 2.f * _PI;

constexpr float pow(float number, int n);
constexpr int fact(int n);

constexpr float sqrt(float n);

constexpr float degToRad(float angle);
constexpr float cos(float angle);
constexpr float sin(float angle);
constexpr float acos(float angle);
constexpr float asin(float angle);
constexpr float atan(float angle);
} // namespace Maths

#include "Maths.ipp"

static_assert(Maths::pow(3, 2) == 9);
static_assert(Maths::pow(4, 3) == 64);
static_assert(Maths::pow(2, 6) == 64);

static_assert(Maths::fact(1) == 1);
static_assert(Maths::fact(3) == 6);
static_assert(Maths::fact(5) == 120);

static_assert(Maths::sqrt(1.f) == 1.f);
static_assert(Maths::sqrt(4.f) == 2.f);
static_assert(Maths::sqrt(100.f) == 10.f);

constexpr bool almostEquals(float a, float b)
{
    return std::abs(a - b) < 0.001f;
}
static_assert(almostEquals(Maths::cos(0.f), 1.f));
static_assert(almostEquals(Maths::cos(Maths::_PI_2), 0.f));
static_assert(almostEquals(Maths::cos(Maths::_PI), -1.f));
static_assert(almostEquals(Maths::cos(Maths::_PI + Maths::_PI_2), 0.f));
static_assert(almostEquals(Maths::cos(-Maths::_PI_2), 0.f));

// static_assert(almostEquals(Maths::acos(1.f), 0.f));
static_assert(almostEquals(Maths::acos(0.5f), Maths::_PI / 3.f));
static_assert(almostEquals(Maths::acos(0.f), Maths::_PI_2));
static_assert(almostEquals(Maths::acos(-0.5f), 2 * Maths::_PI / 3.f));
// static_assert(almostEquals(Maths::acos(-1.f), Maths::_PI));
