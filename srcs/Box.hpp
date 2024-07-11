#pragma once

#include "Vector.hpp"

class Box
{
public:
    constexpr Box();

    constexpr void SetMinX(double value) { m_min.x = value; }
    constexpr void SetMinY(double value) { m_min.y = value; }
    constexpr void SetMinZ(double value) { m_min.z = value; }
    constexpr void SetMaxX(double value) { m_max.x = value; }
    constexpr void SetMaxY(double value) { m_max.y = value; }
    constexpr void SetMaxZ(double value) { m_max.z = value; }

    constexpr bool Contains(const Vector& point) const;

private:
    Vector m_min;
    Vector m_max;
};
