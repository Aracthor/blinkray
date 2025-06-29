#pragma once

#include "Geometry.hpp"

class LimitInGeom final : public Limits
{
public:
    constexpr LimitInGeom(const Geometry& geom, const Vector& position, const Matrix& rotation)
        : m_geom(geom)
        , m_position(position)
        , m_rotation(rotation)
    {
    }

    constexpr bool Contains(const Vector& point) const override
    {
        const Vector pointInRepere = m_rotation * point + m_position;
        return m_geom.Contains(pointInRepere);
    }

private:
    const Geometry& m_geom;
    Vector m_position;
    Matrix m_rotation;
};
