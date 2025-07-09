#include "Image.hpp"
#include "Raytracer.hpp"
#include "Scene.hpp"

#include <unistd.h>

#ifndef SCENE_FILE
#error "scene file must be indicated through macro SCENE_FILE."
#else
#include SCENE_FILE
#endif

#ifndef IMAGE_WIDTH
#define IMAGE_WIDTH 800
#endif
#ifndef IMAGE_HEIGHT
#define IMAGE_HEIGHT 600
#endif

constexpr int imageWidth = IMAGE_WIDTH;
constexpr int imageHeight = IMAGE_HEIGHT;

constexpr Scene scene = CreateScene();

constexpr auto ProcessImage()
{
    constexpr Raytracer raytracer = Raytracer(scene.Objects(), scene.Lights());
    constexpr const Camera* camera = scene.GetCamera();

    auto image = new Image<imageWidth, imageHeight>();
    for (int y = 0; y < imageHeight; y++)
    {
        for (int x = 0; x < imageWidth; x++)
        {
            const double pixelX = double(x - imageWidth / 2) / double(imageWidth);
            const double pixelY = double(imageHeight / 2 - y) / double(imageHeight);
            const Ray ray = camera->GetRay(pixelX, pixelY);
            const Vector newPosition = camera->Rotation() * ray.origin + camera->Position();
            const Vector newDirection = camera->Rotation() * ray.dir;
            const Ray transformedRay(newPosition, newDirection);
            const Color pixelColor = raytracer.ProjectRay(transformedRay);
            image->SetPixel(x, y, pixelColor);
        }
    }
    auto result = image->ToBitmapFile();
    delete image;
    return result;
}

int main(int argc, char** argv)
{
    constexpr auto imageFile = ProcessImage();
    const ssize_t writed = write(STDOUT_FILENO, imageFile.data(), imageFile.size());
    if (writed != static_cast<ssize_t>(imageFile.size()))
        return 1;
    return 0;
}
