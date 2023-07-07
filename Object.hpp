#pragma once

#include "Color.hpp"
#include "Matrix.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Object
{
public:
    constexpr Object(const Vector& position, const Matrix& rotation, const Color& color)
        : m_position(position)
        , m_rotation(rotation)
        , m_invertRotation(rotation.Invert())
        , m_color(color)
    {
    }

    constexpr const Vector& GetPosition() const { return m_position; }
    constexpr const Matrix& GetRotation() const { return m_rotation; }
    constexpr const Matrix& GetInvertRotation() const { return m_invertRotation; }
    constexpr const Color& GetColor() const { return m_color; }

    constexpr virtual Optional<float> IntersectionDistance(const Ray& ray) const = 0;
    constexpr virtual Vector GetNormal(const Vector& rayOrigin, const Vector& position) const = 0;

private:
    Vector m_position;
    Matrix m_rotation;
    Matrix m_invertRotation;
    Color m_color;
};
