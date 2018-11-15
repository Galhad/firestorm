// MIT License
//
// Copyright (c) 2018 Wojciech Wilk
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
