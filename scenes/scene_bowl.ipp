#include "Scene.hpp"

#include "cameras/PerspectiveCamera.hpp"
#include "geometries/Cylinder.hpp"
#include "geometries/Plane.hpp"
#include "geometries/Sphere.hpp"
#include "lights/AmbientLight.hpp"
#include "lights/SpotLight.hpp"
#include "limits/LimitInBox.hpp"
#include "limits/LimitInGeom.hpp"
#include "limits/LimitOpposite.hpp"
#include "materials/Checkboard.hpp"
#include "materials/SimpleColor.hpp"

#include "Image.hpp"

constexpr Matrix bowlRepere;
constexpr Matrix bowlBottomRepere;
constexpr Matrix waterRepere;
constexpr Matrix cylinderRepere = Matrix::RotationMatrixAroundX(Maths::degToRad(-40.0));
constexpr Matrix planeRepere;

constexpr SimpleColor bowlMat(Color(0.8, 0.5, 0.3, 1.0));
constexpr SimpleColor waterMat(Color(0.4, 0.5, 1.0, 0.3), 0.0, 1.33);
constexpr SimpleColor cylinderMat(Color(0.0, 1.0, 0.0, 1.0));
constexpr SimpleColor checkboardWhite(Colors::white);
constexpr SimpleColor checkboardBlack(Colors::black);
constexpr Checkboard planeMat(&checkboardWhite, &checkboardBlack, 10.0);

constexpr Box bowlBox = []
{
    Box box;
    box.SetMaxZ(-2.0);
    return box;
}();
constexpr Sphere bowlGeom(30.0);
constexpr LimitInBox bowlLimits(bowlBox);
constexpr Object bowl(bowlGeom, Vector(0.0, 0.0, 0.0), bowlRepere, bowlMat, &bowlLimits);

constexpr Vector planePosition(0.0, 0.0, -23.0);
constexpr Vector waterPosition(0.0, 0.0, -8.0);
constexpr LimitInGeom inBowlLimit(bowlGeom, planePosition, bowlBottomRepere);
constexpr LimitInGeom waterInBowlLimit(bowlGeom, waterPosition, waterRepere);
constexpr LimitOpposite outBowlLimit(inBowlLimit);

constexpr Plane waterGeom;
constexpr Object water(waterGeom, waterPosition, waterRepere, waterMat, &waterInBowlLimit);

constexpr Plane bowlBottomGeom;
constexpr Object bowlBottom(bowlBottomGeom, planePosition, bowlBottomRepere, bowlMat, &inBowlLimit);

constexpr Cylinder cylinderGeom(5.0);
constexpr Object cylinder(cylinderGeom, Vector(0.0, 10.0, 0.0), cylinderRepere, cylinderMat);

constexpr Plane planeGeom;
constexpr Object plane(planeGeom, planePosition, planeRepere, planeMat, &outBowlLimit);

constexpr AmbientLight ambientLight(Color(0.2, 0.2, 0.2, 1.0));
constexpr SpotLight spotLight(Colors::white, Vector(0.0, -20.0, 60.0), 40.0);

constexpr Vector cameraPos(-50.0, 0.0, 0.0);
constexpr Matrix cameraMatrix = Matrix::RotationMatrixAroundY(Maths::degToRad(-25.0));
constexpr PerspectiveCamera perspCamera(cameraPos, cameraMatrix, 80.0, 60.0, 50.0);

constexpr auto CreateScene()
{
    const std::array objects = {
        &bowl, &bowlBottom, &plane, &water, &cylinder,
    };
    const std::array lights = {
        (const Light*)&ambientLight,
        (const Light*)&spotLight,
    };
    const Camera* camera = &perspCamera;
    return Scene(camera, objects, lights);
}
