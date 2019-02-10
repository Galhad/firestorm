


#include "TransformationComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace fs::scene
{
void TransformationComponent::create(SceneNode& sceneNode)
{
    Component::create(sceneNode);

    TransformationComponent::transform = {};
    position = {0.f, 0.f};
    rotation = {0.f, 0.f, 0.f};
    layer = 0.f;
    scale = {1.f, 1.f};
    transformUpdated = true;
}

void TransformationComponent::destroy()
{
    transform = {};
    transformUpdated = true;

    Component::destroy();
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
    transformUpdated = true;
}

core::fs_float32 TransformationComponent::getLayer() const
{
    return layer;
}

void TransformationComponent::setLayer(core::fs_float32 layer)
{
    TransformationComponent::layer = layer;
    transformUpdated = true;
}

core::Vector3f TransformationComponent::getRotation() const
{
    return rotation;
}

void TransformationComponent::setRotation(core::fs_float32 rotation)
{
    TransformationComponent::rotation.z = rotation;
    transformUpdated = true;
}

void TransformationComponent::setRotation(core::Vector3f rotation)
{
    TransformationComponent::rotation = rotation;
    transformUpdated = true;
}

core::Vector2f TransformationComponent::getScale() const
{
    return scale;
}

void TransformationComponent::setScale(core::fs_float32 x, core::fs_float32 y)
{
    scale.x = x;
    scale.y = y;
    transformUpdated = true;
}

void TransformationComponent::setScale(core::Vector2f scale)
{
    TransformationComponent::scale = scale;
    transformUpdated = true;
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


bool TransformationComponent::isTransformUpdated() const
{
    return transformUpdated;
}

void TransformationComponent::updateTransform()
{
    calculateModelMatrix();
    transformUpdated = false;
}

const graphics::Transform& TransformationComponent::getTransform() const
{
    return transform;
}

void TransformationComponent::setTransformUpdated(bool geometryUpdated)
{
    TransformationComponent::transformUpdated = geometryUpdated;
}
}
