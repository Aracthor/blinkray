#pragma once

#include "Coord2D.hpp"
#include "Material.hpp"
#include "Matrix.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Object
{
public:
    constexpr Object(const Vector& position, const Matrix& rotation, const Material& material)
        : m_position(position)
        , m_rotation(rotation)
        , m_invertRotation(rotation.Invert())
        , m_material(material)
    {
    }

    constexpr const Vector& GetPosition() const { return m_position; }
    constexpr const Matrix& GetRotation() const { return m_rotation; }
    constexpr const Matrix& GetInvertRotation() const { return m_invertRotation; }
    constexpr const Material& GetMaterial() const { return m_material; }

    constexpr virtual Optional<float> IntersectionDistance(const Ray& ray) const = 0;
    constexpr virtual Vector GetNormal(const Vector& rayOrigin, const Vector& position) const = 0;
    constexpr virtual Coord2D GetUV(const Vector& position) const = 0;

private:
    Vector m_position;
    Matrix m_rotation;
    Matrix m_invertRotation;
    const Material& m_material;
};
