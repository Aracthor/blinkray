#pragma once

#include "Color.hpp"
#include "Coord2D.hpp"

class Material
{
public:
    constexpr Material(float reflection)
        : m_reflection(reflection)
    {
    }

    constexpr float GetReflection() const { return m_reflection; }

    virtual constexpr Color GetColor(Coord2D uv) const = 0;

private:
    const float m_reflection;
};
