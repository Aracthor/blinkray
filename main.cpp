#include "Image.hpp"
#include "Scene.hpp"
#include "Vector.hpp"

#include "scene_test.ipp"

#include <unistd.h>

constexpr int imageWidth = 80;
constexpr int imageHeight = 60;

constexpr float cameraFowWidth = 80;
constexpr float cameraFowHeight = 60;
constexpr float cameraFowDistance = 50;

constexpr Scene scene = CreateScene();

struct Intersection
{
    Vector position{};
    Vector normal{};
    const Object* object{};
};

template <size_t objectN>
constexpr Optional<Intersection>
ClosestIntersection(const Ray& ray, const std::array<const Object*, objectN>& objects)
{
    Optional<Intersection> result;
    for (const Object* object : objects)
    {
        const Ray rayInRepere = ray.Transform(object->GetPosition(), object->GetRotation());
        const Optional<float> intersectionDistance = object->IntersectionDistance(rayInRepere);
        if (intersectionDistance)
        {
            const Matrix invertRotation = object->GetInvertRotation();
            const Vector intersectionInRepere = rayInRepere.AtDistance(*intersectionDistance);
            const Vector intersectionPoint = ray.AtDistance(*intersectionDistance);
            const Vector objectNormal = object->GetNormal(rayInRepere.origin, intersectionInRepere);
            const Vector normal = invertRotation * objectNormal;
            const float distanceSq = (ray.origin - intersectionPoint).LengthSq();
            if (!result || distanceSq < (ray.origin - result->position).LengthSq())
                result = {intersectionPoint, normal, object};
        }
    }
    return result;
}

constexpr void ApplyLightIfPracticable(const Intersection& intersection, const SpotLight& light,
                                       Color& pixelColor)
{
    const Ray lightRay = light.RayToPosition(intersection.position);
    const Optional<Intersection> lightIntersection = ClosestIntersection(lightRay, scene.objects);
    if (lightIntersection && lightIntersection->object == intersection.object)
    {
        const float lightPower = light.LightPower(intersection.position, intersection.normal);
        pixelColor += intersection.object->GetColor() * lightPower;
    }
}

constexpr Color ProcessPixelColor(int x, int y)
{
    Color pixelColor = Colors::black;
    const Vector origin = Vector(-100.f, 0.f, 0.f);
    float targetX = cameraFowDistance;
    float targetY = float(x - imageWidth / 2) / float(imageWidth) * cameraFowWidth;
    float targetZ = float(imageHeight / 2 - y) / float(imageHeight) * cameraFowHeight;
    const Vector target = Vector(targetX, targetY, targetZ);
    const Ray ray = {origin, target};

    const Optional<Intersection> intersection = ClosestIntersection(ray, scene.objects);
    if (intersection)
    {
        for (const SpotLight& light : scene.lights)
        {
            ApplyLightIfPracticable(*intersection, light, pixelColor);
        }
    }

    return pixelColor;
}

constexpr auto ProcessImage()
{
    auto image = Image<imageWidth, imageHeight>();
    for (int y = 0; y < imageHeight; y++)
    {
        for (int x = 0; x < imageWidth; x++)
        {
            Color pixelColor = ProcessPixelColor(x, y);
            image.SetPixel(x, y, pixelColor);
        }
    }
    return image.ToBitmapFile();
}

int main(int argc, char** argv)
{
    constexpr auto imageFile = ProcessImage();
    if (write(STDOUT_FILENO, imageFile.data(), imageFile.size()) != imageFile.size())
        return 1;
    return 0;
}