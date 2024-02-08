#include "Image.hpp"
#include "Raytracer.hpp"
#include "Scene.hpp"

#include <unistd.h>

#ifndef SCENE_FILE
#error "scene file must be indicated through macro SCENE_FILE."
#else
#include SCENE_FILE
#endif

constexpr int imageWidth = 80;
constexpr int imageHeight = 60;

constexpr Scene scene = CreateScene();

constexpr auto ProcessImage()
{
    constexpr Raytracer raytracer = Raytracer(scene.Objects(), scene.Lights());
    constexpr const Camera* camera = scene.GetCamera();

    auto image = Image<imageWidth, imageHeight>();
    for (int y = 0; y < imageHeight; y++)
    {
        for (int x = 0; x < imageWidth; x++)
        {
            const double pixelX = double(x - imageWidth / 2) / double(imageWidth);
            const double pixelY = double(imageHeight / 2 - y) / double(imageHeight);
            const Ray ray = camera->GetRay(pixelX, pixelY);
            const Ray transformedRay = ray.Transform(-camera->Position(), camera->InvertRotation());
            const Color pixelColor = raytracer.ProjectRay(transformedRay);
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
