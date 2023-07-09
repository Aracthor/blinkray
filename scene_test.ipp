#include "Scene.hpp"

#include "materials/Checkboard.hpp"
#include "materials/SimpleColor.hpp"
#include "objects/Cone.hpp"
#include "objects/Cylinder.hpp"
#include "objects/Plane.hpp"
#include "objects/Sphere.hpp"

constexpr Matrix rSphereRepere = Matrix();
constexpr Matrix planeRepere = Matrix();
constexpr Matrix rCylindRepere = Matrix::RotationMatrixAroundX(Maths::degToRad(30.f));
constexpr Matrix bConeRepere = Matrix();

constexpr SimpleColor rSphereMat = SimpleColor(Colors::red);
constexpr Checkboard planeMat = Checkboard(Colors::white, Colors::black, 10.f);
constexpr SimpleColor rCylindMat = SimpleColor(Colors::red);
constexpr SimpleColor bConeMat = SimpleColor(Colors::blue);

constexpr Sphere rSphere = Sphere(Vector(0.f, -20.f, 0.f), rSphereRepere, rSphereMat, 30.f);
constexpr Plane plane = Plane(Vector(0.f, 0.f, -40.f), planeRepere, planeMat);
constexpr Cylinder rCylinder = Cylinder(Vector(0.f, -20.f, 0.f), rCylindRepere, rCylindMat, 20.f);
constexpr Cone bCone = Cone(Vector(0.f, -20.f, 0.f), bConeRepere, bConeMat, Maths::degToRad(30.f));

constexpr auto CreateScene()
{
    const std::array objects = {
        (const Object*)&bCone,
        (const Object*)&plane,
    };
    const std::array lights = {
        SpotLight(Vector(-30.f, -50.f, 30.f), 10.f),
        SpotLight(Vector(-40.f, 30.f, -10.f), 20.f),
    };
    return Scene(objects, lights);
}
