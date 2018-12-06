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

#ifndef FIRESTORM_SPRITE_HPP
#define FIRESTORM_SPRITE_HPP

#include "Texture.hpp"
#include "Mesh.hpp"
#include "vulkan/GraphicsPipeline.hpp"

#include <memory>

namespace fs::graphics
{
class Sprite
{
public:
    Sprite() = default;
    virtual ~Sprite() = default;

    void create(core::Recti rect, const Texture& texture, const GraphicsPipeline& graphicsPipeline);
    virtual void destroy();

    const Texture* getTexture() const;
    const VkDescriptorSet getDescriptorSet() const;

    Mesh& getMesh();
    const Mesh& getMesh() const;

    core::fs_float32 getWidthUnits() const;
    core::fs_float32 getHeightUnits() const;

private:
    void createDescriptor();
    void destroyDescriptor();

    void createMesh();
    void destroyMesh();

private:
    Mesh mesh;

    core::Recti rect;
    const Texture* texture = nullptr;

    core::fs_float32 widthUnits = 0.f;
    core::fs_float32 heightUnits = 0.f;

    VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
    VkWriteDescriptorSet writeDescriptorSet = {};
    const GraphicsPipeline* pipeline = nullptr;

};

typedef std::unique_ptr<Sprite> SpritePtr;
}

#endif //FIRESTORM_SPRITE_HPP
