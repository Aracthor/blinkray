#pragma once

#include "Vector.hpp"

class Limits
{
public:
    constexpr Limits();

    constexpr Limits& SetMinX(double value);
    constexpr Limits& SetMinY(double value);
    constexpr Limits& SetMinZ(double value);
    constexpr Limits& SetMaxX(double value);
    constexpr Limits& SetMaxY(double value);
    constexpr Limits& SetMaxZ(double value);

    constexpr bool Contains(const Vector& point) const;

private:
    Vector m_min;
    Vector m_max;
};

#include "Limits.ipp"
