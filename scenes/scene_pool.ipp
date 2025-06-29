#include "Scene.hpp"

#include "cameras/PerspectiveCamera.hpp"
#include "geometries/Plane.hpp"
#include "lights/AmbientLight.hpp"
#include "lights/SpotLight.hpp"
#include "materials/Textured.hpp"

#include "Image.hpp"

#include "../assets/tile_square_pool_col.bmp.inl"
constexpr auto tile_square_pool_color_texture = ImageFromBitmapFile<tile_square_pool_col>();

constexpr Matrix planeRepere;

constexpr Textured planeMat(tile_square_pool_color_texture, 100.0, 0.0);

constexpr Plane planeGeom;
constexpr Object plane(planeGeom, Vector(0.0, 0.0, -50.0), planeRepere, planeMat);

constexpr AmbientLight ambientLight(Color(0.03, 0.03, 0.03, 1.0));
constexpr SpotLight spotLight(Colors::white, Vector(0.0, 60.0, 40.0), 50.0);

constexpr Vector cameraPos(-100.0, 0.0, 0.0);
constexpr Matrix cameraMatrix = Matrix::RotationMatrixAroundX(Maths::degToRad(0.0));
constexpr PerspectiveCamera perspCamera(cameraPos, cameraMatrix, 80.0, 60.0, 50.0);

constexpr auto CreateScene()
{
    const std::array objects = {
        &plane,
    };
    const std::array lights = {
        (const Light*)&ambientLight,
        (const Light*)&spotLight,
    };
    const Camera* camera = &perspCamera;
    return Scene(camera, objects, lights);
}
