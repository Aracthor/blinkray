#include "Scene.hpp"

#include "cameras/PerspectiveCamera.hpp"
#include "geometries/Plane.hpp"
#include "lights/AmbientLight.hpp"
#include "lights/SpotLight.hpp"
#include "limits/LimitInBox.hpp"
#include "limits/LimitOpposite.hpp"
#include "materials/SimpleColor.hpp"
#include "materials/Textured.hpp"

#include "Image.hpp"

#include "../assets/tile_square_pool_col.bmp.inl"
constexpr auto tile_square_pool_color_texture = ImageFromBitmapFile<tile_square_pool_col>();

constexpr Matrix planeRepere;

constexpr Textured poolMat(tile_square_pool_color_texture, 20.0, 0.0, 1.0);
constexpr SimpleColor waterMat(Color(0.4, 0.5, 0.8, 0.3), 0.3, 1.33);

constexpr Box poolBox = []
{
    Box box;
    box.SetMinX(-12.5);
    box.SetMaxX(12.5);
    box.SetMinY(-25.0);
    box.SetMaxY(25.0);
    return box;
}();

constexpr Box poolWidthBox = []
{
    Box box;
    box.SetMinX(-12.5);
    box.SetMaxX(12.5);
    box.SetMinY(-5.0);
    box.SetMaxY(5.0);
    return box;
}();

constexpr Box poolHeightBox = []
{
    Box box;
    box.SetMinX(-5.0);
    box.SetMaxX(5.0);
    box.SetMinY(-25.0);
    box.SetMaxY(25.0);
    return box;
}();

constexpr LimitInBox limitInPool(poolBox);
constexpr LimitOpposite limitOutPool(limitInPool);
constexpr LimitInBox limitPoolWidthFloor(poolWidthBox);
constexpr LimitInBox limitPoolHeightFloor(poolHeightBox);

constexpr Plane planeGeom;
constexpr Object floor(planeGeom, Vector(0.0, 0.0, 0.0), planeRepere, poolMat, &limitOutPool);

constexpr Object water(planeGeom, Vector(0.0, 0.0, -1.0), planeRepere, waterMat);

constexpr Matrix leftPoolMatrix = Matrix::RotationMatrixAroundX(Maths::degToRad(90.0));
constexpr Object leftPoolWall(planeGeom, Vector(0.0, -25.0, -5.0), leftPoolMatrix, poolMat, &limitPoolWidthFloor);
constexpr Matrix rightPoolMatrix = Matrix::RotationMatrixAroundX(Maths::degToRad(-90.0));
constexpr Object rightPoolWall(planeGeom, Vector(0.0, 25.0, -5.0), rightPoolMatrix, poolMat, &limitPoolWidthFloor);
constexpr Matrix frontPoolMatrix = Matrix::RotationMatrixAroundY(Maths::degToRad(90.0));
constexpr Object frontPoolWall(planeGeom, Vector(-12.5, 0.0, -5.0), frontPoolMatrix, poolMat, &limitPoolHeightFloor);
constexpr Matrix backPoolMatrix = Matrix::RotationMatrixAroundY(Maths::degToRad(-90.0));
constexpr Object backPoolWall(planeGeom, Vector(12.5, 0.0, -5.0), backPoolMatrix, poolMat, &limitPoolHeightFloor);

constexpr Object poolBottom(planeGeom, Vector(0.0, 0.0, -10.0), planeRepere, poolMat, &limitInPool);

constexpr AmbientLight ambientLight(Color(0.03, 0.03, 0.03, 1.0));
constexpr SpotLight spotLight1(Colors::white, Vector(0.0, 30.0, 40.0), 40.0);
constexpr SpotLight spotLight2(Colors::white, Vector(40.0, -30.0, 40.0), 40.0);

constexpr Vector cameraPos(-20.0, -15.0, 20.0);
constexpr Matrix cameraMatrix = Matrix::RotationMatrixAroundY(Maths::degToRad(50.0));
constexpr PerspectiveCamera perspCamera(cameraPos, cameraMatrix, 80.0, 60.0, 50.0);

constexpr auto CreateScene()
{
    const std::array objects = {
        &floor, &water, &leftPoolWall, &rightPoolWall, &frontPoolWall, &backPoolWall, &poolBottom,
    };
    const std::array lights = {
        (const Light*)&ambientLight,
        (const Light*)&spotLight1,
        (const Light*)&spotLight2,
    };
    const Camera* camera = &perspCamera;
    return Scene(camera, objects, lights);
}
