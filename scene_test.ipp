#include "Scene.hpp"

#include "materials/Checkboard.hpp"
#include "materials/SimpleColor.hpp"
#include "objects/Cylinder.hpp"
#include "objects/Plane.hpp"
#include "objects/Sphere.hpp"

constexpr Matrix rSphereRepere = Matrix();
constexpr Matrix planeRepere = Matrix();
constexpr Matrix bCylindRepere = Matrix::RotationMatrixAroundX(Maths::degToRad(0.f));

constexpr SimpleColor rSphereMat = SimpleColor(0.0f, Colors::red);
constexpr Checkboard planeMat = Checkboard(0.5f, Colors::white, Colors::black, 10.f);
constexpr SimpleColor bCylindMat = SimpleColor(0.f, Colors::blue);

constexpr Sphere rSphere = Sphere(Vector(50.f, -20.f, 0.f), rSphereRepere, rSphereMat, 30.f);
constexpr Plane plane = Plane(Vector(0.f, 0.f, -40.f), planeRepere, planeMat);
constexpr Cylinder bCylinder = Cylinder(Vector(0.f, 30.f, 0.f), bCylindRepere, bCylindMat, 20.f);

constexpr SpotLight whiteSpotLight = SpotLight(Colors::white, Vector(10.f, -180.f, 160.f), 60.f);
constexpr SpotLight yellowSpotLight = SpotLight(Colors::yellow, Vector(0.f, 60.f, 40.f), 30.f);

constexpr auto CreateScene()
{
    const std::array objects = {
        (const Object*)&rSphere,
        (const Object*)&plane,
    };
    const std::array lights = {
        &whiteSpotLight,
        &yellowSpotLight,
    };
    return Scene(objects, lights);
}
