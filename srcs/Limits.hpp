#pragma once

#include "Box.hpp"

class Limits
{
public:
    constexpr Limits() = default;
    constexpr Limits(const Box& box)
        : m_box(box)
    {
    }

    constexpr bool Contains(const Vector& point) const { return m_box.Contains(point); }

private:
    Box m_box;
};

#include "Box.ipp"
