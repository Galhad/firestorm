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

#ifndef FIRESTORM_TEXTUREIMAGE_HPP
#define FIRESTORM_TEXTUREIMAGE_HPP

#include "Image.hpp"
#include "Buffer.hpp"

#include <memory>
#include <cstdint>
#include <stdint-gcc.h>

namespace fs::graphics
{
class TextureImage : public Image
{
public:
    TextureImage() = default;
    ~TextureImage() override = default;

    void create(const Device& device, core::fs_uint32 width, core::fs_uint32 height, const std::vector<core::fs_uint8>& bytes);
    void destroy() override;

protected:
    Buffer buffer;

protected:
    void copyBufferToImage(core::fs_uint32 width, core::fs_uint32 height);
};

typedef std::unique_ptr<TextureImage> TextureImagePtr;
}

#endif //FIRESTORM_TEXTUREIMAGE_HPP
