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

#include "SpriteRendererComponent.hpp"

namespace fs::scene
{
void SpriteRendererComponent::create(SceneNode& sceneNode, TransformationComponent& transformation,
                                     const graphics::Sprite& sprite)
{
    RendererComponent::create(sceneNode, transformation);
    SpriteRendererComponent::sprite = &sprite;
}

void SpriteRendererComponent::destroy()
{
    sprite = nullptr;
    RendererComponent::destroy();
}

void SpriteRendererComponent::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout,
                                     VkDescriptorSet sceneDescriptorSet)
{
    if (!active)
    {
        return;
    }

    pushTransform(commandBuffer, pipelineLayout);

    std::array<VkDescriptorSet, 2> descriptorSets = {sceneDescriptorSet, sprite->getDescriptorSet()};

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0,
                            static_cast<uint32_t>(descriptorSets.size()), descriptorSets.data(), 0, nullptr);

    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(sprite->getMesh().getIndices().size()), 1, 0,
                     sprite->getMesh().getIndexBase(), 0);
}

const fs::graphics::Sprite* SpriteRendererComponent::getSprite() const
{
    return sprite;
}

void SpriteRendererComponent::setSprite(const fs::graphics::Sprite& sprite)
{
    SpriteRendererComponent::sprite = &sprite;
}

}
