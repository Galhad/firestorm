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

#include "SpriteSceneNode.hpp"

#include "graphics/vulkan/Vertex.hpp"

namespace fs::scene
{

void SpriteSceneNode::create(const graphics::Sprite& sprite)
{
    SceneNode::create();

    SpriteSceneNode::sprite = &sprite;
}

void SpriteSceneNode::destroy()
{
    sprite = nullptr;

    SceneNode::destroy();
}

void SpriteSceneNode::update(float deltaTime)
{

}

void
SpriteSceneNode::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
                        VkDescriptorSet sceneDescriptorSet)
{
    SceneNode::render(commandBuffer, pipelineLayout, sceneDescriptorSet);

    std::array<VkDescriptorSet, 2> descriptorSets = {sceneDescriptorSet, sprite->getDescriptorSet()};

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0,
                            static_cast<uint32_t>(descriptorSets.size()), descriptorSets.data(), 0, nullptr);

    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(sprite->getMesh().getIndices().size()), 1, 0,
                     sprite->getMesh().getIndexBase(), 0);
}

const graphics::Sprite* SpriteSceneNode::getSprite() const
{
    return sprite;
}

void SpriteSceneNode::setSprite(const graphics::Sprite& sprite)
{
    SpriteSceneNode::sprite = &sprite;
}
}
