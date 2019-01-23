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

#include "SpriteSheet.hpp"

namespace fs::graphics
{

void SpriteSheet::create(const fs::graphics::GraphicsPipeline& graphicsPipeline, TextureImage textureImage,
                         core::fs_uint32 width, core::fs_uint32 height,
                         core::fs_uint32 pixelsPerUnit, core::fs_uint32 channels)
{
    Texture::create(textureImage, width, height, pixelsPerUnit, channels);
    SpriteSheet::graphicsPipeline = &graphicsPipeline;
    spritesChanged = true;

    createDescriptor();
}

void SpriteSheet::destroy()
{
    clearSprites();
    destroyDescriptor();

    graphicsPipeline = nullptr;

    Texture::destroy();
}

Sprite* SpriteSheet::addSprite(core::Recti rect)
{
    auto& sprite = sprites.emplace_back();
    sprite.create(rect, *this, descriptorSet);
    spritesChanged = true;
    return &sprite;
}

bool SpriteSheet::removeSprite(Sprite* sprite)
{
    spritesChanged = true;
    return false;
}

void SpriteSheet::clearSprites()
{
    for (auto& sprite : sprites)
    {
        sprite.destroy();
    }
    sprites.clear();
    spritesChanged = true;
}

const std::list<Sprite>& SpriteSheet::getSprites() const
{
    return sprites;
}

std::list<Sprite>& SpriteSheet::getSprites()
{
    return sprites;
}

bool SpriteSheet::areSpritesChanged() const
{
    return spritesChanged;
}

void SpriteSheet::setSpritesChanged(bool spritesChanged)
{
    SpriteSheet::spritesChanged = spritesChanged;
}

void SpriteSheet::createDescriptor()
{
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = graphicsPipeline->getDescriptorPool();
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &graphicsPipeline->getMaterialDescriptorSetLayout();

    vkAllocateDescriptorSets(graphicsPipeline->getSwapChain()->getDevice()->getDevice(), &allocInfo, &descriptorSet);

    VkWriteDescriptorSet writeDescriptorSet = {};
    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSet.dstSet = descriptorSet;
    writeDescriptorSet.dstBinding = 0;
    writeDescriptorSet.dstArrayElement = 0;
    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeDescriptorSet.descriptorCount = 1;
    writeDescriptorSet.pImageInfo = &getTextureImage().getDescriptorImageInfo();

    vkUpdateDescriptorSets(graphicsPipeline->getSwapChain()->getDevice()->getDevice(), 1, &writeDescriptorSet, 0,
                           nullptr);
}

void SpriteSheet::destroyDescriptor()
{
    descriptorSet = VK_NULL_HANDLE;
}

}

