#pragma once

#include "Vector.hpp"

class Limits
{
public:
    constexpr Limits();

    constexpr Limits& SetMinX(float value);
    constexpr Limits& SetMinY(float value);
    constexpr Limits& SetMinZ(float value);
    constexpr Limits& SetMaxX(float value);
    constexpr Limits& SetMaxY(float value);
    constexpr Limits& SetMaxZ(float value);

    constexpr bool Contains(const Vector& point) const;

private:
    Vector m_min;
    Vector m_max;
};

#include "Limits.ipp"
