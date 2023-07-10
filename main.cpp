#include "Image.hpp"
#include "Raytracer.hpp"
#include "Scene.hpp"

#include "scene_test.ipp"

#include <unistd.h>

constexpr int imageWidth = 80;
constexpr int imageHeight = 60;

constexpr float cameraFowWidth = 80;
constexpr float cameraFowHeight = 60;
constexpr float cameraFowDistance = 50;

constexpr Scene scene = CreateScene();

constexpr Color ProcessPixelColor(int x, int y)
{
    constexpr Raytracer raytracer = Raytracer(scene);
    const Vector origin = Vector(-100.f, 0.f, 0.f);
    float targetX = cameraFowDistance;
    float targetY = float(x - imageWidth / 2) / float(imageWidth) * cameraFowWidth;
    float targetZ = float(imageHeight / 2 - y) / float(imageHeight) * cameraFowHeight;
    const Vector target = Vector(targetX, targetY, targetZ);
    const Ray ray = {origin, target};

    return raytracer.ProjectRay(ray);
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
    const ssize_t writed = write(STDOUT_FILENO, imageFile.data(), imageFile.size());
    if (writed != static_cast<ssize_t>(imageFile.size()))
        return 1;
    return 0;
}