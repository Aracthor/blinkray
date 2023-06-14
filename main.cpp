#include "Image.hpp"

#include <unistd.h>

constexpr auto ProcessImage()
{
    auto image = Image<80, 60>();
    image.SetPixel(30, 40, Color(0xFF, 0x00, 0xFF, 0xFF));
    image.SetPixel(30, 41, Color(0xFF, 0x00, 0xFF, 0xFF));
    image.SetPixel(31, 40, Color(0xFF, 0x00, 0xFF, 0xFF));
    image.SetPixel(10, 40, Color(0x00, 0xFF, 0xFF, 0xFF));
    image.SetPixel(10, 20, Color(0x00, 0xFF, 0xFF, 0xFF));
    image.SetPixel(0, 30, Color(0x00, 0xFF, 0xFF, 0x80));
    image.SetPixel(0, 40, Color(0x00, 0xFF, 0xFF, 0x80));
    return image.ToBitmapFile();
}

int main(int argc, char** argv)
{
    constexpr auto imageFile = ProcessImage();
    write(STDOUT_FILENO, imageFile.data(), imageFile.size());
    return 0;
}