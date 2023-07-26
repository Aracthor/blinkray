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

constexpr auto ProcessImage()
{
    constexpr Raytracer raytracer = Raytracer(scene.Objects(), scene.Lights());
    constexpr const Camera& camera = scene.GetCamera();

    auto image = Image<imageWidth, imageHeight>();
    for (int y = 0; y < imageHeight; y++)
    {
        for (int x = 0; x < imageWidth; x++)
        {
            const float pixelX = float(x - imageWidth / 2) / float(imageWidth);
            const float pixelY = float(imageHeight / 2 - y) / float(imageHeight);
            const Ray ray = camera.GetRay(pixelX, pixelY);
            const Color pixelColor = raytracer.ProjectRay(ray);
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