#include <limits>

constexpr float limitMin = std::numeric_limits<float>::lowest();
constexpr float limitMax = std::numeric_limits<float>::max();

constexpr Limits::Limits()
    : m_min(limitMin, limitMin, limitMin)
    , m_max(limitMax, limitMax, limitMax)
{
}

constexpr Limits& Limits::SetMinX(float value)
{
    m_min.x = value;
    return *this;
}

constexpr Limits& Limits::SetMinY(float value)
{
    m_min.y = value;
    return *this;
}

constexpr Limits& Limits::SetMinZ(float value)
{
    m_min.z = value;
    return *this;
}

constexpr Limits& Limits::SetMaxX(float value)
{
    m_max.x = value;
    return *this;
}

constexpr Limits& Limits::SetMaxY(float value)
{
    m_max.y = value;
    return *this;
}

constexpr Limits& Limits::SetMaxZ(float value)
{
    m_max.z = value;
    return *this;
}

constexpr bool Limits::Contains(const Vector& point) const
{
    return point.x > m_min.x && point.y > m_min.y && point.z > m_min.z && point.x < m_max.x && point.y < m_max.y &&
           point.z < m_max.z;
}
