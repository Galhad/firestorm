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

#include "Sprite.hpp"

namespace fs::graphics
{
void Sprite::create(core::Recti rect, const Texture& texture, const GraphicsPipeline& graphicsPipeline)
{
    this->rect = rect;
    this->texture = &texture;
    this->pipeline = &graphicsPipeline;

    createDescriptor();

    createMesh();
}

void Sprite::createDescriptor()
{
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = pipeline->getDescriptorPool();
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &pipeline->getMaterialDescriptorSetLayout();

    vkAllocateDescriptorSets(pipeline->getSwapChain()->getDevice()->getDevice(), &allocInfo, &descriptorSet);

    writeDescriptorSet = {};
    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSet.dstSet = descriptorSet;
    writeDescriptorSet.dstBinding = 0;
    writeDescriptorSet.dstArrayElement = 0;
    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeDescriptorSet.descriptorCount = 1;
    writeDescriptorSet.pImageInfo = &texture->getTextureImage().getDescriptorImageInfo();

    vkUpdateDescriptorSets(pipeline->getSwapChain()->getDevice()->getDevice(), 1, &writeDescriptorSet, 0,
                           nullptr);
}

void Sprite::createMesh()
{
    auto width = static_cast<core::fs_float32>(rect.width) / texture->getPixelsPerUnit();
    auto height = static_cast<core::fs_float32>(rect.height) / texture->getPixelsPerUnit();

    core::Rectf textureRect{};
    textureRect.x = static_cast<core::fs_float32>(rect.x) / texture->getWidthPixels();
    textureRect.y = static_cast<core::fs_float32>(rect.y) / texture->getHeightPixels();
    textureRect.width = static_cast<core::fs_float32>(rect.width) / texture->getWidthPixels();
    textureRect.height = static_cast<core::fs_float32>(rect.height) / texture->getHeightPixels();

    std::vector<Vertex> vertices;
    vertices.push_back({
                           {0.f,           0.f,  0.f},
                           {1.0f,          0.0f, 0.0f},
                           {textureRect.x, textureRect.y}
                       });
    vertices.push_back({
                           {width,                             0.f,  0.f},
                           {0.0f,                              1.0f, 0.0f},
                           {textureRect.x + textureRect.width, textureRect.y}
                       });
    vertices.push_back({
                           {width,                             height, 0.f},
                           {0.0f,                              0.0f,   1.0f},
                           {textureRect.x + textureRect.width, textureRect.y + textureRect.height}
                       });
    vertices.push_back({
                           {0.f,           height, 0.f},
                           {1.0f,          1.0f,   1.0f},
                           {textureRect.x, textureRect.y + textureRect.height}
                       });

    const std::vector<core::fs_uint32> indices{0, 1, 2, 2, 3, 0};

    mesh.create(vertices, indices);
}

void Sprite::destroy()
{
    destroyMesh();

    destroyDescriptor();

    texture = nullptr;
    pipeline = nullptr;
}

void Sprite::destroyMesh()
{
    mesh.destroy();
}

void Sprite::destroyDescriptor()
{
    descriptorSet = VK_NULL_HANDLE;
    writeDescriptorSet = {};
}

const VkDescriptorSet Sprite::getDescriptorSet() const
{
    return descriptorSet;
}

const Texture* Sprite::getTexture() const
{
    return texture;
}

Mesh& Sprite::getMesh()
{
    return mesh;
}

const Mesh& Sprite::getMesh() const
{
    return mesh;
}
}
