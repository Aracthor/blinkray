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
constexpr Matrix bCylindRepere = Matrix::RotationMatrixAroundX(Maths::degToRad(0.f));

constexpr SimpleColor rSphereMat = SimpleColor(0.0f, Colors::red);
constexpr SimpleColor checkboardWhite = SimpleColor(0.5f, Colors::white);
constexpr SimpleColor checkboardBlack = SimpleColor(0.5f, Colors::black);
constexpr Checkboard planeMat = Checkboard(&checkboardWhite, &checkboardBlack, 10.f);
constexpr SimpleColor bCylindMat = SimpleColor(0.f, Colors::blue);

constexpr Sphere rSphere = Sphere(Vector(50.f, -20.f, 0.f), rSphereRepere, rSphereMat, 30.f);
constexpr Plane plane = Plane(Vector(0.f, 0.f, -40.f), planeRepere, planeMat);
constexpr Cylinder bCylinder = Cylinder(Vector(80.f, -80.f, 0.f), bCylindRepere, bCylindMat, 20.f);

constexpr AmbientLight ambientLight = AmbientLight(Color(0.03f, 0.03f, 0.03f, 1.f));
constexpr DirectionalLight whiteDirLight = DirectionalLight(Color(0.2f, 0.2f, 0.2f, 1.f), Vector(-0.1f, 0.2f, -0.8f));
constexpr SpotLight yellowSpotLight = SpotLight(Colors::yellow, Vector(0.f, 60.f, 40.f), 50.f);

constexpr Vector cameraPos = Vector(-100.f, 0.f, 0.f);
constexpr Matrix cameraMatrix = Matrix::RotationMatrixAroundX(Maths::degToRad(0.f));
constexpr PerspectiveCamera perspCamera = PerspectiveCamera(cameraPos, cameraMatrix, 80.f, 60.f, 50.f);
constexpr OrthographicCamera orthoCamera = OrthographicCamera(cameraPos, cameraMatrix, 80.f, 60.f);

constexpr float azimuthAngle = Maths::degToRad(80.f);
constexpr float siteAngle = Maths::degToRad(60.f);
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
