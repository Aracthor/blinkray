#pragma once

#include "Box.hpp"

class LimitInBox final : public Limits
{
public:
    constexpr LimitInBox(const Box& box)
        : m_box(box)
    {
    }

    constexpr bool Contains(const Vector& point) const override { return m_box.Contains(point); }

private:
    Box m_box;
};

#include "Box.ipp"
