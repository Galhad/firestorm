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

#ifndef FIRESTORM_TEXTURE_HPP
#define FIRESTORM_TEXTURE_HPP

#include "core/Types.hpp"
#include "vulkan/TextureImage.hpp"

#include <memory>

namespace fs::graphics
{

class Texture
{
public:
    Texture() = default;
    virtual ~Texture() = default;

    void create(TextureImage textureImage, core::fs_uint32 width, core::fs_uint32 height,
                core::fs_uint32 pixelsPerUnit = 100, core::fs_uint32 channels = 4);
    virtual void destroy();

    core::fs_uint32 getWidthPixels() const;
    core::fs_float32 getWidthUnits() const;

    core::fs_uint32 getHeightPixels() const;
    core::fs_float32 getHeightUnits() const;

    core::fs_uint32 getChannels() const;

    const TextureImage& getTextureImage() const;

    core::fs_uint32 getPixelsPerUnit() const;

protected:
    core::fs_uint32 width = 0;
    core::fs_uint32 height = 0;
    core::fs_uint32 channels = 0;
    TextureImage textureImage;
    core::fs_uint32 pixelsPerUnit = 100;
};

typedef std::unique_ptr<Texture> TexturePtr;
}

#endif //FIRESTORM_TEXTURE_HPP
