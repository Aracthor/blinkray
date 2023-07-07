#include "Scene.hpp"

#include "Plane.hpp"
#include "Sphere.hpp"

constexpr Matrix rSphereRepere = Matrix();
constexpr Matrix gPlaneRepere = Matrix::RotationMatrixAroundX(Maths::degToRad(90.f));

constexpr Sphere rSphere = Sphere(Vector(0.f, -20.f, 0.f), rSphereRepere, Colors::red, 30.f);
constexpr Plane gPlane = Plane(Vector(0.f, -40.f, 0.f), gPlaneRepere, Colors::green);

constexpr auto CreateScene()
{
    const std::array objects = {
        (const Object*)&rSphere,
        (const Object*)&gPlane,
    };
    const std::array lights = {
        SpotLight(Vector(-20.f, 50.f, 30.f), 30.f),
        SpotLight(Vector(-40.f, 30.f, -10.f), 20.f),
    };
    constexpr int objectN = std::size(objects);
    constexpr int lightN = std::size(lights);
    return Scene<objectN, lightN>(objects, lights);
}
