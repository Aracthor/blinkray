#include "Image.hpp"
#include "Scene.hpp"
#include "Vector.hpp"

#include "scene_test.ipp"

#include <unistd.h>

constexpr int imageWidth = 160;
constexpr int imageHeight = 120;

constexpr float cameraFowWidth = 80;
constexpr float cameraFowHeight = 60;
constexpr float cameraFowDistance = 50;

constexpr Scene scene = CreateScene();

constexpr Color ProcessPixelColor(int x, int y)
{
    Vector origin = Vector(-100.f, 0.f, 0.f);
    float targetX = cameraFowDistance;
    float targetY = float(x - imageWidth / 2) / float(imageWidth) * cameraFowWidth;
    float targetZ = float(y - imageHeight / 2) / float(imageHeight) * cameraFowHeight;
    Vector target = Vector(targetX, targetY, targetZ);
    const std::optional<Vector> intersection = scene.object.Intersection(origin, target);
    if (intersection)
    {
        const Vector normal = scene.object.GetNormal(*intersection);
        const float lightPower = scene.light.LightPower(*intersection, normal);
        return scene.object.GetColor() * lightPower;
    }

    return Color(0x00, 0x00, 0x00, 0xFF);
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
    write(STDOUT_FILENO, imageFile.data(), imageFile.size());
    return 0;
}