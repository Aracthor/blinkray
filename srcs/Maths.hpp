#pragma once

namespace Maths
{
constexpr double _PI = 3.14159265359;
constexpr double _PI_2 = _PI / 2.0;
constexpr double _2_PI = 2.0 * _PI;

constexpr double pow(double number, int n);
constexpr int fact(int n);

constexpr double sqrt(double n);

constexpr double degToRad(double angle);
constexpr double cos(double angle);
constexpr double sin(double angle);
constexpr double acos(double angle);
constexpr double asin(double angle);
} // namespace Maths

#include "Maths.ipp"

static_assert(Maths::pow(3, 2) == 9);
static_assert(Maths::pow(4, 3) == 64);
static_assert(Maths::pow(2, 6) == 64);

static_assert(Maths::fact(1) == 1);
static_assert(Maths::fact(3) == 6);
static_assert(Maths::fact(5) == 120);

static_assert(Maths::sqrt(1.0) == 1.0);
static_assert(Maths::sqrt(4.0) == 2.0);
static_assert(Maths::sqrt(100.0) == 10.0);

constexpr bool almostEquals(double a, double b)
{
    return std::abs(a - b) < 0.001f;
}
static_assert(almostEquals(Maths::cos(0.0), 1.0));
static_assert(almostEquals(Maths::cos(Maths::_PI_2), 0.0));
static_assert(almostEquals(Maths::cos(Maths::_PI), -1.0));
static_assert(almostEquals(Maths::cos(Maths::_PI + Maths::_PI_2), 0.0));
static_assert(almostEquals(Maths::cos(-Maths::_PI_2), 0.0));

static_assert(almostEquals(Maths::sin(0.0), 0.0));
static_assert(almostEquals(Maths::sin(Maths::_PI_2), 1.0));
static_assert(almostEquals(Maths::sin(Maths::_PI), 0.0));
static_assert(almostEquals(Maths::sin(Maths::_PI + Maths::_PI_2), -1.0));
static_assert(almostEquals(Maths::sin(-Maths::_PI_2), -1.0));

// static_assert(almostEquals(Maths::acos(1.0), 0.0));
static_assert(almostEquals(Maths::acos(0.5), Maths::_PI / 3.0));
static_assert(almostEquals(Maths::acos(0.0), Maths::_PI_2));
static_assert(almostEquals(Maths::acos(-0.5), 2 * Maths::_PI / 3.0));
// static_assert(almostEquals(Maths::acos(-1.0), Maths::_PI));
