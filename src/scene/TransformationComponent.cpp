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

#include "TransformationComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace fs::scene
{
void TransformationComponent::create()
{
    TransformationComponent::transform = {};
    position = {0.f, 0.f};
    rotation = {0.f, 0.f, 0.f};
    layer = 0.f;
    scale = {1.f, 1.f};
    geometryUpdated = true;
}

void TransformationComponent::destroy()
{
    transform = {};
    geometryUpdated = true;
}

core::Vector2f TransformationComponent::getPosition() const
{
    return position;
}

void TransformationComponent::setPosition(core::fs_float32 x, core::fs_float32 y)
{
    position.x = x;
    position.y = y;
}

void TransformationComponent::setPosition(core::Vector2f position)
{
    TransformationComponent::position = position;
    geometryUpdated = true;
}

core::fs_float32 TransformationComponent::getLayer() const
{
    return layer;
}

void TransformationComponent::setLayer(core::fs_float32 layer)
{
    TransformationComponent::layer = layer;
    geometryUpdated = true;
}

core::Vector3f TransformationComponent::getRotation() const
{
    return rotation;
}

void TransformationComponent::setRotation(core::fs_float32 rotation)
{
    TransformationComponent::rotation.z = rotation;
    geometryUpdated = true;
}

void TransformationComponent::setRotation(core::Vector3f rotation)
{
    TransformationComponent::rotation = rotation;
    geometryUpdated = true;
}

core::Vector2f TransformationComponent::getScale() const
{
    return scale;
}

void TransformationComponent::setScale(core::fs_float32 x, core::fs_float32 y)
{
    scale.x = x;
    scale.y = y;
    geometryUpdated = true;
}

void TransformationComponent::setScale(core::Vector2f scale)
{
    TransformationComponent::scale = scale;
    geometryUpdated = true;
}

void TransformationComponent::calculateModelMatrix()
{
    core::fs_mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, layer));
    core::Vector3f rotationRad = core::Vector3f{glm::radians(rotation.x), glm::radians(rotation.y),
                                                glm::radians(rotation.z)};
    core::fs_mat4 rotation = glm::toMat4(core::Quaternion(rotationRad));
    core::fs_mat4 scale = glm::scale(glm::mat4(1.0f),
                                     glm::vec3(TransformationComponent::scale.x, TransformationComponent::scale.y,
                                               1.0f));
    transform.model = translation * rotation * scale;
}


bool TransformationComponent::isGeometryUpdated() const
{
    return geometryUpdated;
}

void TransformationComponent::updateTransform()
{
    calculateModelMatrix();
    geometryUpdated = false;
}

const graphics::Transform& TransformationComponent::getTransform() const
{
    return transform;
}

void TransformationComponent::setGeometryUpdated(bool geometryUpdated)
{
    TransformationComponent::geometryUpdated = geometryUpdated;
}
}
