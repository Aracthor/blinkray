#include "Scene.hpp"

constexpr auto CreateScene()
{
    const std::array objects = {
        Sphere(Vector(0.f, 20.f, 0.f), Color(0xFF, 0x00, 0x00, 0xFF), 30.f),
        Sphere(Vector(20.f, -30.f, 10.f), Color(0x00, 0xFF, 0x00, 0xFF), 40.f),
    };
    const std::array lights = {
        SpotLight(Vector(-20.f, 50.f, -30.f), 30.f),
        SpotLight(Vector(-20.f, -50.f, -50.f), 20.f),
    };
    constexpr int objectN = std::size(objects);
    constexpr int lightN = std::size(lights);
    return Scene<objectN, lightN>(objects, lights);
}
