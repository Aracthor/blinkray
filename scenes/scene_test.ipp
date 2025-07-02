#include "Scene.hpp"

#include "cameras/FishEyeCamera.hpp"
#include "cameras/OrthographicCamera.hpp"
#include "cameras/PerspectiveCamera.hpp"
#include "geometries/Cylinder.hpp"
#include "geometries/Plane.hpp"
#include "geometries/Sphere.hpp"
#include "lights/AmbientLight.hpp"
#include "lights/DirectionalLight.hpp"
#include "lights/SpotLight.hpp"
#include "limits/LimitInBox.hpp"
#include "materials/Checkboard.hpp"
#include "materials/SimpleColor.hpp"

constexpr Matrix rSphereRepere;
constexpr Matrix planeRepere;
constexpr Matrix bCylindRepere = Matrix::RotationMatrixAroundX(Maths::degToRad(0.0));

constexpr SimpleColor rSphereMat(Colors::red, 0.0);
constexpr SimpleColor checkboardWhite(Colors::white, 0.0);
constexpr SimpleColor checkboardBlack(Colors::black, 0.5);
constexpr Checkboard planeMat(&checkboardWhite, &checkboardBlack, 10.0);
constexpr SimpleColor bCylindMat(Color(0.0, 0.0, 1.0, 0.5), 0.0);

constexpr Box rSphereBox = []
{
    Box box;
    box.SetMinX(-15.0);
    box.SetMaxY(25.0);
    return box;
}();
constexpr Sphere rSphereGeom(30.0);
constexpr LimitInBox rSphereLimits(rSphereBox);
constexpr Object rSphere(rSphereGeom, Vector(50.0, -20.0, -10.0), rSphereRepere, rSphereMat, &rSphereLimits);
constexpr Plane planeGeom;
constexpr Object plane(planeGeom, Vector(0.0, 0.0, -40.0), planeRepere, planeMat);
constexpr Cylinder bCylinderGeom(20.0);
constexpr Object bCylinder(bCylinderGeom, Vector(80.0, -80.0, 0.0), bCylindRepere, bCylindMat);

constexpr AmbientLight ambientLight(Color(0.03, 0.03, 0.03, 1.0));
constexpr DirectionalLight whiteDirLight(Color(0.2, 0.2, 0.2, 1.0), Vector(-0.1, 0.2, -0.8));
constexpr SpotLight yellowSpotLight(Colors::yellow, Vector(0.0, 60.0, 40.0), 50.0);

constexpr Vector cameraPos(-100.0, 0.0, 0.0);
constexpr Matrix cameraMatrix = Matrix::RotationMatrixAroundX(Maths::degToRad(0.0));
constexpr PerspectiveCamera perspCamera(cameraPos, cameraMatrix, 80.0, 60.0, 50.0);
constexpr OrthographicCamera orthoCamera(cameraPos, cameraMatrix, 80.0, 60.0);

constexpr double azimuthAngle = Maths::degToRad(80.0);
constexpr double siteAngle = Maths::degToRad(60.0);
constexpr FishEyeCamera fishEyeCamera(cameraPos, cameraMatrix, azimuthAngle, siteAngle);

constexpr auto CreateScene()
{
    const std::array objects = {
        &rSphere,
        &plane,
        &bCylinder,
    };
    const std::array lights = {
        (const Light*)&ambientLight,
        (const Light*)&whiteDirLight,
        (const Light*)&yellowSpotLight,
    };
    const Camera* camera = &perspCamera;
    return Scene(camera, objects, lights);
}
