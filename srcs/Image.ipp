#include <cstdint>

constexpr int pixelSize = sizeof(unsigned char) * 4;

template <std::size_t SIZE, int N>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, const uint8_t (&array)[N])
{
    for (int i = 0; i < N; i++)
        data[writeIndex++] = (char)(array[i]);
}

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, uint16_t n)
{
    data[writeIndex++] = (char)(n >> 0);
    data[writeIndex++] = (char)(n >> 8);
}

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, uint32_t n)
{
    data[writeIndex++] = (char)(n >> 0);
    data[writeIndex++] = (char)(n >> 8);
    data[writeIndex++] = (char)(n >> 16);
    data[writeIndex++] = (char)(n >> 24);
}

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, int32_t n)
{
    data[writeIndex++] = (char)(n >> 0);
    data[writeIndex++] = (char)(n >> 8);
    data[writeIndex++] = (char)(n >> 16);
    data[writeIndex++] = (char)(n >> 24);
}

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, Color c)
{
    data[writeIndex++] = (char)((unsigned char)(c.r * 255));
    data[writeIndex++] = (char)((unsigned char)(c.g * 255));
    data[writeIndex++] = (char)((unsigned char)(c.b * 255));
    data[writeIndex++] = (char)((unsigned char)(c.a * 255));
}

struct __attribute__((packed)) BmpPV4Header
{
    constexpr BmpPV4Header(int width, int height)
        : width(width)
        , height(height)
        , rawDataSize(width * height * pixelSize)
    {
    }

    uint32_t headerSize = sizeof(BmpPV4Header);
    int32_t width;
    int32_t height;
    uint16_t planes = 1;
    uint16_t bpp = 0x20;
    uint32_t compression = 3;
    uint32_t rawDataSize;
    int32_t hResolution = 0;
    int32_t vResolution = 0;
    uint32_t paletteSize = 0;
    uint32_t importantColors = 0;
    uint32_t channelMaskRed = 0x000000FF;
    uint32_t channelMaskGreen = 0x0000FF00;
    uint32_t channelMaskBlue = 0x00FF0000;
    uint32_t channelMaskAlpha = 0xFF000000;
    uint32_t csType = 0x57696E20; // "Win "
    uint8_t colorSpaceEndpoints[0x24] = {};
    uint32_t gammaRed = 0;
    uint32_t gammaGreen = 0;
    uint32_t gammaBlue = 0;
};

struct __attribute__((packed)) BmpHeader
{
    constexpr BmpHeader(int size)
        : size(size)
    {
    }

    uint16_t magic = 0x4D42;
    uint32_t size;
    uint16_t app1 = 0;
    uint16_t app2 = 0;
    uint32_t offset = sizeof(BmpHeader) + sizeof(BmpPV4Header);
};

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, const BmpHeader& header)
{
    WriteInData(data, writeIndex, header.magic);
    WriteInData(data, writeIndex, header.size);
    WriteInData(data, writeIndex, header.app1);
    WriteInData(data, writeIndex, header.app2);
    WriteInData(data, writeIndex, header.offset);
}

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, const BmpPV4Header& infoHeader)
{
    WriteInData(data, writeIndex, infoHeader.headerSize);
    WriteInData(data, writeIndex, infoHeader.width);
    WriteInData(data, writeIndex, infoHeader.height);
    WriteInData(data, writeIndex, infoHeader.planes);
    WriteInData(data, writeIndex, infoHeader.bpp);
    WriteInData(data, writeIndex, infoHeader.compression);
    WriteInData(data, writeIndex, infoHeader.rawDataSize);
    WriteInData(data, writeIndex, infoHeader.hResolution);
    WriteInData(data, writeIndex, infoHeader.vResolution);
    WriteInData(data, writeIndex, infoHeader.paletteSize);
    WriteInData(data, writeIndex, infoHeader.importantColors);
    WriteInData(data, writeIndex, infoHeader.channelMaskRed);
    WriteInData(data, writeIndex, infoHeader.channelMaskGreen);
    WriteInData(data, writeIndex, infoHeader.channelMaskBlue);
    WriteInData(data, writeIndex, infoHeader.channelMaskAlpha);
    WriteInData(data, writeIndex, infoHeader.csType);
    WriteInData(data, writeIndex, infoHeader.colorSpaceEndpoints);
    WriteInData(data, writeIndex, infoHeader.gammaRed);
    WriteInData(data, writeIndex, infoHeader.gammaGreen);
    WriteInData(data, writeIndex, infoHeader.gammaBlue);
}

template <int WIDTH, int HEIGHT>
constexpr auto Image<WIDTH, HEIGHT>::ToBitmapFile() const
{
    constexpr int size = sizeof(BmpHeader) + sizeof(BmpPV4Header) + pixelSize * WIDTH * HEIGHT;
    BmpHeader header = BmpHeader(size);
    BmpPV4Header infoHeader = BmpPV4Header(WIDTH, HEIGHT);
    std::array<char, size> data = {};
    int writeIndex = 0;
    WriteInData(data, writeIndex, header);
    WriteInData(data, writeIndex, infoHeader);
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < WIDTH; x++)
            WriteInData(data, writeIndex, m_pixels[y * WIDTH + x]);
    }
    return data;
}
