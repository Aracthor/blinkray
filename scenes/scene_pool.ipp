#include "Scene.hpp"

#include "cameras/PerspectiveCamera.hpp"
#include "lights/AmbientLight.hpp"
#include "lights/SpotLight.hpp"
#include "materials/Textured.hpp"
#include "objects/Plane.hpp"

#include "Image.hpp"

#include "../assets/tile_square_pool_col.bmp.inl"
constexpr auto tile_square_pool_color_texture = ImageFromBitmapFile<tile_square_pool_col>();

constexpr Matrix planeRepere = Matrix();

constexpr Textured planeMat = Textured(tile_square_pool_color_texture, 100.0, 0.0);

constexpr Plane plane = Plane(Vector(0.0, 0.0, -50.0), planeRepere, {}, planeMat);

constexpr AmbientLight ambientLight = AmbientLight(Color(0.03, 0.03, 0.03, 1.0));
constexpr SpotLight spotLight = SpotLight(Colors::white, Vector(0.0, 60.0, 40.0), 50.0);

constexpr Vector cameraPos = Vector(-100.0, 0.0, 0.0);
constexpr Matrix cameraMatrix = Matrix::RotationMatrixAroundX(Maths::degToRad(0.0));
constexpr PerspectiveCamera perspCamera = PerspectiveCamera(cameraPos, cameraMatrix, 80.0, 60.0, 50.0);

constexpr auto CreateScene()
{
    const std::array objects = {
        (const Object*)&plane,
    };
    const std::array lights = {
        (const Light*)&ambientLight,
        (const Light*)&spotLight,
    };
    const Camera* camera = &perspCamera;
    return Scene(camera, objects, lights);
}
