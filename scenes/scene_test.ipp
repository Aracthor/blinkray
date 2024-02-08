#include "Scene.hpp"

#include "cameras/FishEyeCamera.hpp"
#include "cameras/OrthographicCamera.hpp"
#include "cameras/PerspectiveCamera.hpp"
#include "lights/AmbientLight.hpp"
#include "lights/DirectionalLight.hpp"
#include "lights/SpotLight.hpp"
#include "materials/Checkboard.hpp"
#include "materials/SimpleColor.hpp"
#include "objects/Cylinder.hpp"
#include "objects/Plane.hpp"
#include "objects/Sphere.hpp"

constexpr Matrix rSphereRepere = Matrix();
constexpr Matrix planeRepere = Matrix();
constexpr Matrix bCylindRepere = Matrix::RotationMatrixAroundX(Maths::degToRad(0.0));

constexpr SimpleColor rSphereMat = SimpleColor(0.0, 1.0, Colors::red);
constexpr SimpleColor checkboardWhite = SimpleColor(0.0, 1.0, Colors::white);
constexpr SimpleColor checkboardBlack = SimpleColor(0.5, 1.0, Colors::black);
constexpr Checkboard planeMat = Checkboard(&checkboardWhite, &checkboardBlack, 10.0);
constexpr SimpleColor bCylindMat = SimpleColor(0.0, 0.5, Colors::blue);

constexpr Limits sphereLimits = Limits().SetMinX(-15.0).SetMaxY(25.0);
constexpr Sphere rSphere = Sphere(Vector(50.0, -20.0, -10.0), rSphereRepere, sphereLimits, rSphereMat, 30.0);
constexpr Plane plane = Plane(Vector(0.0, 0.0, -40.0), planeRepere, {}, planeMat);
constexpr Cylinder bCylinder = Cylinder(Vector(80.0, -80.0, 0.0), bCylindRepere, {}, bCylindMat, 20.0);

constexpr AmbientLight ambientLight = AmbientLight(Color(0.03, 0.03, 0.03, 1.0));
constexpr DirectionalLight whiteDirLight = DirectionalLight(Color(0.2, 0.2, 0.2, 1.0), Vector(-0.1, 0.2, -0.8));
constexpr SpotLight yellowSpotLight = SpotLight(Colors::yellow, Vector(0.0, 60.0, 40.0), 50.0);

constexpr Vector cameraPos = Vector(-100.0, 0.0, 0.0);
constexpr Matrix cameraMatrix = Matrix::RotationMatrixAroundX(Maths::degToRad(0.0));
constexpr PerspectiveCamera perspCamera = PerspectiveCamera(cameraPos, cameraMatrix, 80.0, 60.0, 50.0);
constexpr OrthographicCamera orthoCamera = OrthographicCamera(cameraPos, cameraMatrix, 80.0, 60.0);

constexpr double azimuthAngle = Maths::degToRad(80.0);
constexpr double siteAngle = Maths::degToRad(60.0);
constexpr FishEyeCamera fishEyeCamera = FishEyeCamera(cameraPos, cameraMatrix, azimuthAngle, siteAngle);

constexpr auto CreateScene()
{
    const std::array objects = {
        (const Object*)&rSphere,
        (const Object*)&plane,
        (const Object*)&bCylinder,
    };
    const std::array lights = {
        (const Light*)&ambientLight,
        (const Light*)&whiteDirLight,
        (const Light*)&yellowSpotLight,
    };
    const Camera* camera = &perspCamera;
    return Scene(camera, objects, lights);
}
