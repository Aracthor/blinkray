#include "Scene.hpp"

constexpr Scene CreateScene()
{
    const Sphere object = Sphere(30.f, Color(0xFF, 0x00, 0x00, 0xFF));
    const SpotLight light = SpotLight(Vector(-20.f, 50.f, -30.f), 30.f);
    return {object, light};
}
