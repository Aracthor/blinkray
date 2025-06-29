#pragma once

class LimitOpposite final : public Limits
{
public:
    constexpr LimitOpposite(const Limits& limits)
        : m_limits(limits)
    {
    }

    constexpr bool Contains(const Vector& point) const override { return !m_limits.Contains(point); }

private:
    const Limits& m_limits;
};
