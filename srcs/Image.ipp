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

template <const uint8_t* DATA, typename T>
constexpr typename std::enable_if<std::is_same<T, uint16_t>::value, uint16_t>::type ReadFromData(int& readIndex)
{
    uint16_t result = 0;
    result += (uint16_t)(DATA[readIndex++]) << 0;
    result += (uint16_t)(DATA[readIndex++]) << 8;
    return result;
}

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, uint32_t n)
{
    data[writeIndex++] = (char)(n >> 0);
    data[writeIndex++] = (char)(n >> 8);
    data[writeIndex++] = (char)(n >> 16);
    data[writeIndex++] = (char)(n >> 24);
}

template <const uint8_t* DATA, typename T>
constexpr typename std::enable_if<std::is_same<T, uint32_t>::value, uint32_t>::type ReadFromData(int& readIndex)
{
    uint32_t result = 0;
    result += (uint32_t)(DATA[readIndex++]) << 0;
    result += (uint32_t)(DATA[readIndex++]) << 8;
    result += (uint32_t)(DATA[readIndex++]) << 16;
    result += (uint32_t)(DATA[readIndex++]) << 24;
    return result;
}

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, int32_t n)
{
    data[writeIndex++] = (char)(n >> 0);
    data[writeIndex++] = (char)(n >> 8);
    data[writeIndex++] = (char)(n >> 16);
    data[writeIndex++] = (char)(n >> 24);
}

template <const uint8_t* DATA, typename T>
constexpr typename std::enable_if<std::is_same<T, int32_t>::value, int32_t>::type ReadFromData(int& readIndex)
{
    int32_t result = 0;
    result += (int32_t)(DATA[readIndex++]) << 0;
    result += (int32_t)(DATA[readIndex++]) << 8;
    result += (int32_t)(DATA[readIndex++]) << 16;
    result += (int32_t)(DATA[readIndex++]) << 24;
    return result;
}

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, Color c)
{
    data[writeIndex++] = (char)((unsigned char)(c.r * 255));
    data[writeIndex++] = (char)((unsigned char)(c.g * 255));
    data[writeIndex++] = (char)((unsigned char)(c.b * 255));
    data[writeIndex++] = (char)((unsigned char)(c.a * 255));
}

template <const uint8_t* DATA, typename T>
constexpr typename std::enable_if<std::is_same<T, Color>::value, Color>::type ReadFromData(int readIndex)
{
    Color result;
    result.b = (float)(DATA[readIndex++]) / 255.f;
    result.g = (float)(DATA[readIndex++]) / 255.f;
    result.r = (float)(DATA[readIndex++]) / 255.f;
    result.a = (float)(DATA[readIndex++]) / 255.f;
    return result;
}

struct __attribute__((packed)) BmpPV5Header
{
    constexpr BmpPV5Header() = default;
    constexpr BmpPV5Header(int width, int height)
        : width(width)
        , height(height)
        , rawDataSize(width * height * pixelSize)
    {
    }

    uint32_t headerSize = sizeof(BmpPV5Header);
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
    uint32_t intent = 0x4; // LCS_GM_ABS_COLORIMETRIC
    uint32_t profileData = 0;
    uint32_t profileSize = 0;
    uint32_t reserved = 0;
};

struct __attribute__((packed)) BmpHeader
{
    constexpr BmpHeader() = default;
    constexpr BmpHeader(int size)
        : size(size)
    {
    }

    uint16_t magic = 0x4D42;
    uint32_t size;
    uint16_t app1 = 0;
    uint16_t app2 = 0;
    uint32_t offset = sizeof(BmpHeader) + sizeof(BmpPV5Header);
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

template <const uint8_t* DATA, typename T>
constexpr typename std::enable_if<std::is_same<T, BmpHeader>::value, BmpHeader>::type ReadFromData(int readIndex)
{
    BmpHeader header;
    header.magic = ReadFromData<DATA, uint16_t>(readIndex);
    header.size = ReadFromData<DATA, uint32_t>(readIndex);
    header.app1 = ReadFromData<DATA, uint16_t>(readIndex);
    header.app2 = ReadFromData<DATA, uint16_t>(readIndex);
    header.offset = ReadFromData<DATA, uint32_t>(readIndex);
    return header;
}

template <std::size_t SIZE>
constexpr void WriteInData(std::array<char, SIZE>& data, int& writeIndex, const BmpPV5Header& infoHeader)
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
    WriteInData(data, writeIndex, infoHeader.intent);
    WriteInData(data, writeIndex, infoHeader.profileData);
    WriteInData(data, writeIndex, infoHeader.profileSize);
    WriteInData(data, writeIndex, infoHeader.reserved);
}

template <const uint8_t* DATA, typename T>
constexpr typename std::enable_if<std::is_same<T, BmpPV5Header>::value, BmpPV5Header>::type ReadFromData(int readIndex)
{
    BmpPV5Header infoHeader;
    infoHeader.headerSize = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.width = ReadFromData<DATA, int32_t>(readIndex);
    infoHeader.height = ReadFromData<DATA, int32_t>(readIndex);
    infoHeader.planes = ReadFromData<DATA, uint16_t>(readIndex);
    infoHeader.bpp = ReadFromData<DATA, uint16_t>(readIndex);
    infoHeader.compression = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.rawDataSize = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.hResolution = ReadFromData<DATA, int32_t>(readIndex);
    infoHeader.vResolution = ReadFromData<DATA, int32_t>(readIndex);
    infoHeader.paletteSize = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.importantColors = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.channelMaskRed = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.channelMaskGreen = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.channelMaskBlue = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.channelMaskAlpha = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.csType = ReadFromData<DATA, uint32_t>(readIndex);
    for (int i = 0; i < 0x24; i++)
        infoHeader.colorSpaceEndpoints[i] = (uint8_t)DATA[readIndex++];
    infoHeader.gammaRed = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.gammaGreen = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.gammaBlue = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.intent = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.profileData = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.profileSize = ReadFromData<DATA, uint32_t>(readIndex);
    infoHeader.reserved = ReadFromData<DATA, uint32_t>(readIndex);
    return infoHeader;
}

template <const char* DATA, int WIDTH, int HEIGHT>
constexpr void ReadPixels(Image<WIDTH, HEIGHT>& image)
{
    int readIndex = sizeof(BmpHeader) + sizeof(BmpPV5Header);
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            Color color = ReadFromData<DATA, Color>(readIndex);
            image.SetPixel(x, y, color);
            readIndex += sizeof(Color);
        }
    }
}

template <int WIDTH, int HEIGHT>
constexpr auto Image<WIDTH, HEIGHT>::ToBitmapFile() const
{
    constexpr int size = sizeof(BmpHeader) + sizeof(BmpPV5Header) + pixelSize * WIDTH * HEIGHT;
    BmpHeader header = BmpHeader(size);
    BmpPV5Header infoHeader = BmpPV5Header(WIDTH, HEIGHT);
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

template <const uint8_t* DATA>
constexpr static auto ImageFromBitmapFile()
{
    constexpr BmpHeader header = ReadFromData<DATA, BmpHeader>(0);
    static_assert(header.magic == 0x4D42);
    static_assert(header.offset == sizeof(BmpHeader) + sizeof(BmpPV5Header));

    constexpr BmpPV5Header infoHeader = ReadFromData<DATA, BmpPV5Header>(sizeof(BmpHeader));
    static_assert(header.size ==
                  sizeof(BmpHeader) + sizeof(BmpPV5Header) + pixelSize * infoHeader.width * infoHeader.height);

    auto image = Image<infoHeader.width, infoHeader.height>();
    for (int y = 0; y < infoHeader.height; y++)
    {
        for (int x = 0; x < infoHeader.width; x++)
        {
            const int pixelIndex = header.offset + (y * infoHeader.width + x) * pixelSize;
            const Color color = ReadFromData<DATA, Color>(pixelIndex);
            image.SetPixel(x, infoHeader.height - 1 - y, color);
        }
    }
    return image;
}
