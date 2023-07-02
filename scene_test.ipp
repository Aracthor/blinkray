#include "Scene.hpp"

constexpr auto CreateScene()
{
    const Sphere object = Sphere(Vector(0.f, 40.f, 0.f), Color(0xFF, 0x00, 0x00, 0xFF), 30.f);
    const std::array lights = {
        SpotLight(Vector(-20.f, 50.f, -30.f), 30.f),
        SpotLight(Vector(-20.f, -50.f, -50.f), 20.f),
    };
    constexpr int lightN = std::size(lights);
    return Scene<lightN>(object, lights);
}
