#pragma once

#include <utility> // std::pair

#include "Coord2D.hpp"
#include "Geometry.hpp"
#include "Limits.hpp"
#include "Material.hpp"
#include "Matrix.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Object
{
public:
    constexpr Object(const Geometry& geometry, const Vector& position, const Matrix& rotation, const Material& material,
                     const Limits* limits = nullptr);

    constexpr const Vector& GetPosition() const { return m_position; }
    constexpr const Matrix& GetRotation() const { return m_rotation; }
    constexpr const Matrix& GetInvertRotation() const { return m_invertRotation; }
    constexpr const Material& GetMaterial() const { return *m_material; }

    struct Intersection
    {
        Vector position;
        Vector normal;
        Coord2D uv;
        bool entering;
    };

    constexpr std::pair<Optional<Intersection>, Optional<Intersection>> RayIntersection(const Ray& ray) const;

private:
    constexpr Intersection IntersectionData(const Vector& rayOrigin, const Vector& position) const;

    const Geometry* m_geometry;
    Vector m_position;
    Matrix m_rotation;
    Matrix m_invertRotation;
    const Material* m_material;
    const Limits* m_limits;
};

#include "Object.ipp"
