#pragma once

#include <utility> // std::pair

#include "Coord2D.hpp"
#include "Limits.hpp"
#include "Material.hpp"
#include "Matrix.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Object
{
public:
    constexpr Object(const Vector& position, const Matrix& rotation, const Material& material,
                     const Limits* limits = nullptr);

    constexpr const Vector& GetPosition() const { return m_position; }
    constexpr const Matrix& GetRotation() const { return m_rotation; }
    constexpr const Matrix& GetInvertRotation() const { return m_invertRotation; }
    constexpr const Material& GetMaterial() const { return *m_material; }

    constexpr Optional<double> IntersectionDistance(const Ray& ray) const;

    constexpr virtual Vector GetNormal(const Vector& rayOrigin, const Vector& position) const = 0;
    constexpr virtual Coord2D GetUV(const Vector& position) const = 0;

protected:
    using DistancesPair = std::pair<Optional<double>, Optional<double>>;
    constexpr virtual DistancesPair GetIntersectionDistances(const Ray& ray) const = 0;

private:
    Vector m_position;
    Matrix m_rotation;
    Matrix m_invertRotation;
    const Material* m_material;
    const Limits* m_limits;
};

#include "Object.ipp"
