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

#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <cstring>

namespace fs::scene
{

void Camera::create(const graphics::Window& window, const graphics::MappedMemoryBuffer& uniformBuffer, bool active)
{
    Camera::window = &window;
    Camera::active = active;
    Camera::uniformBuffer = &uniformBuffer;
    zoom = 10.f;

    updateUniformData();
    applyUniformData();
}

Camera::~Camera()
{

}

void Camera::destroy()
{
    uniformBuffer = nullptr;
    window = nullptr;
    active = false;

    SceneNode::destroy();
}

bool Camera::isActive() const
{
    return active;
}

void Camera::setActive(bool active)
{
    Camera::active = active;
}

void Camera::setPosition(core::fs_float32 x, core::fs_float32 y)
{
    SceneNode::setPosition(x, y);
}

void Camera::setPosition(core::Vector2f position)
{
    SceneNode::setPosition(position);
}

void Camera::setRotation(core::fs_float32 rotation)
{
    SceneNode::setRotation(rotation);
}

void Camera::setRotation(core::Vector3f rotation)
{
    SceneNode::setRotation(rotation);
}

core::fs_float32 Camera::getZoom() const
{
    return zoom;
}

void Camera::setZoom(core::fs_float32 zoom)
{
    Camera::zoom = zoom;
    geometryUpdated = true;
}

const graphics::Window* Camera::getWindow() const
{
    return window;
}

void Camera::setWindow(const graphics::Window* window)
{
    Camera::window = window;
    updateUniformData();
}

void Camera::applyUniformData()
{
    if (uniformBuffer->getMappedData() != nullptr)
    {
        memcpy(uniformBuffer->getMappedData(), &uniformData, sizeof(graphics::UniformData));
    }
}

void Camera::update(float deltaTime)
{
    if (geometryUpdated && active)
    {
        geometryUpdated = false;
        updateUniformData();
        applyUniformData();
    }
}

void Camera::updateUniformData()
{
    uniformData.view = glm::mat4(1.f);
    uniformData.projection = glm::ortho(position.x, position.x + window->getSize().x / zoom,
                                        position.y + window->getSize().y / zoom, position.y, -1.f, 1.f);
    uniformData.projection[1][1] *= -1;
}

void Camera::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet scenedescriptorSet)
{

}

}
