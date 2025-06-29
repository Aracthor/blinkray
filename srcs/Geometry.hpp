#pragma once

#include <utility> // std::pair

#include "Coord2D.hpp"
#include "Optional.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Geometry
{
public:
    using DistancesPair = std::pair<Optional<double>, Optional<double>>;
    constexpr virtual DistancesPair GetIntersectionDistances(const Ray& ray) const = 0;
    constexpr virtual Vector GetNormal(const Vector& rayOrigin, const Vector& position) const = 0;
    constexpr virtual Coord2D GetUV(const Vector& position) const = 0;
};
