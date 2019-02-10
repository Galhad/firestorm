


#include "Texture.hpp"

namespace fs::graphics
{

void Texture::create(TextureImage textureImage, core::fs_uint32 width, core::fs_uint32 height,
                     core::fs_uint32 pixelsPerUnit, core::fs_uint32 channels)
{
    Texture::textureImage = std::move(textureImage);
    Texture::width = width;
    Texture::height = height;
    Texture::pixelsPerUnit = pixelsPerUnit;
    Texture::channels = channels;
}

void Texture::destroy()
{
    textureImage.destroy();

    width = 0;
    height = 0;
    channels = 0;
}

const TextureImage& Texture::getTextureImage() const
{
    return textureImage;
}

core::fs_uint32 Texture::getWidthPixels() const
{
    return width;
}

core::fs_float32 Texture::getWidthUnits() const
{
    return static_cast<core::fs_float32>(width) / pixelsPerUnit;
}

core::fs_uint32 Texture::getHeightPixels() const
{
    return height;
}

core::fs_float32 Texture::getHeightUnits() const
{
    return static_cast<core::fs_float32>(height) / pixelsPerUnit;
}

core::fs_uint32 Texture::getChannels() const
{
    return channels;
}

core::fs_uint32 Texture::getPixelsPerUnit() const
{
    return pixelsPerUnit;
}
}
