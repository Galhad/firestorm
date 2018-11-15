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

#include <iostream>
#include "SceneNode.hpp"
#include <glm/gtx/transform.hpp>

namespace fs::scene
{

void SceneNode::create(graphics::Sprite& sprite, const graphics::Transform& transform)
{

    SceneNode::sprite = &sprite;
    SceneNode::transform = transform;
    position = {0.f, 0.f};
    layer = 0.f;
    scale = {1.f, 1.f};
    geometryUpdated = true;
}

void SceneNode::destroy()
{
    sprite = nullptr;

    transform = {};
    geometryUpdated = true;
}

void
SceneNode::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet sceneDescriptorSet)
{
    std::array<VkDescriptorSet, 2> descriptorSets = {sceneDescriptorSet, sprite->getDescriptorSet()};

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0,
                            static_cast<uint32_t>(descriptorSets.size()), descriptorSets.data(), 0, nullptr);

    if (geometryUpdated)
    {
        calculateModelMatrix();
        geometryUpdated = false;
    }
    vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(graphics::Transform),
                       &transform);

    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(sprite->getMesh().getIndices().size()), 1, 0,
                     sprite->getMesh().getIndexBase(), 0);
}

graphics::Sprite* SceneNode::getSprite()
{
    return sprite;
}

const graphics::Sprite* SceneNode::getSprite() const
{
    return sprite;
}

void SceneNode::setSprite(graphics::Sprite* sprite)
{
    SceneNode::sprite = sprite;
}

core::Vector2f SceneNode::getPosition() const
{
    return position;
}

void SceneNode::setPosition(core::fs_float32 x, core::fs_float32 y)
{
    position.x = x;
    position.y = y;
}

void SceneNode::setPosition(core::Vector2f position)
{
    SceneNode::position = position;
    geometryUpdated = true;
}

core::fs_float32 SceneNode::getLayer() const
{
    return layer;
}

void SceneNode::setLayer(core::fs_float32 layer)
{
    SceneNode::layer = layer;
    geometryUpdated = true;
}

core::Vector3f SceneNode::getRotation() const
{
    return {0.f, 0.f, 0.f};
}

void SceneNode::setRotation(core::fs_float32 rotation)
{
//    transform.rotation.z = rotation;
}

void SceneNode::setRotation(core::Vector3f rotation)
{
//    transform.rotation = rotation;
}

core::Vector2f SceneNode::getScale() const
{
    return scale;
}

void SceneNode::setScale(core::fs_float32 x, core::fs_float32 y)
{
    scale.x = x;
    scale.y = y;
    geometryUpdated = true;
}

void SceneNode::setScale(core::Vector2f scale)
{
    SceneNode::scale = scale;
    geometryUpdated = true;
}

void SceneNode::calculateModelMatrix()
{
    core::fs_mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, layer));
    core::fs_mat4 scale = glm::scale(glm::vec3(SceneNode::scale.x, SceneNode::scale.y, 1.0f));
    transform.model = translation * scale;
}

}
