#include <limits>

constexpr double limitMin = std::numeric_limits<double>::lowest();
constexpr double limitMax = std::numeric_limits<double>::max();

constexpr Limits::Limits()
    : m_min(limitMin, limitMin, limitMin)
    , m_max(limitMax, limitMax, limitMax)
{
}

constexpr bool Limits::Contains(const Vector& point) const
{
    return point.x > m_min.x && point.y > m_min.y && point.z > m_min.z && point.x < m_max.x && point.y < m_max.y &&
           point.z < m_max.z;
}
