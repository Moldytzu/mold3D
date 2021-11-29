#include <mold3D/3D.h>

using namespace mold;

mold::render::texture::Texture mold::render::texture::LoadRGBBitmap(Text filename)
{
    FILE *file;
    uint32_t size;
    uint16_t bitPlanes;
    uint16_t bpp;

    file = fopen(filename, "rb");

    if ((uint64_t)file == 0)
    {
        char buffer[1024];
        sprintf(buffer, "Couldn't find the bitmap image %s!", filename);

        mold::core::logging::Error(buffer);

        return {};
    }

    BitmapImageHeader *header = (BitmapImageHeader *)malloc(sizeof(BitmapImageHeader));
    if (fread(header, sizeof(BitmapImageHeader), 1, file) != 1)
    {
        char buffer[1024];
        sprintf(buffer, "Couldn't load header from %s!", filename);

        mold::core::logging::Error(buffer);

        return {};
    }

    if (header->BPP != 24)
    {
        char buffer[1024];
        sprintf(buffer, "Unsupported BPP value of %u in file %s, expected 24!", header->BPP, filename);

        mold::core::logging::Error(buffer);

        return {};
    }

    Texture texture;

    texture.Width = header->BitmapWidth;
    texture.Height = header->BitmapHeight;

    texture.PixelData = (Byte *)malloc(header->ImageSize);

    if (fread(texture.PixelData, header->ImageSize, 1, file) != 1)
    {
        char buffer[1024];
        sprintf(buffer, "Couldn't load pixel information from %s!", filename);

        mold::core::logging::Error(buffer);

        return {};
    }

    for (int i = 0; i < header->ImageSize; i += 3)
    { // reverse all of the colors. (bgr -> rgb)

        Byte temp = texture.PixelData[i];

        texture.PixelData[i] = texture.PixelData[i + 2];

        texture.PixelData[i + 2] = temp;
    }

    return texture;
}