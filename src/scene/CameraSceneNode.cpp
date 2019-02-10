


#include "CameraSceneNode.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace fs::scene
{

void CameraSceneNode::create(io::InputManager& inputManager, const graphics::Window& window,
                             const graphics::MappedMemoryBuffer& uniformBuffer)
{
    SceneNode::create(inputManager);

    CameraSceneNode::window = &window;
    CameraSceneNode::active = false;
    CameraSceneNode::uniformBuffer = &uniformBuffer;
    zoom = 10.f;

    updateUniformData();
}

void CameraSceneNode::destroy()
{
    uniformBuffer = nullptr;
    window = nullptr;
    active = false;

    SceneNode::destroy();
}

bool CameraSceneNode::isActive() const
{
    return active;
}

void CameraSceneNode::setActive(bool active)
{
    CameraSceneNode::active = active;
    if (active)
    {
        transformation->setTransformUpdated(true);
    }
}

core::fs_float32 CameraSceneNode::getZoom() const
{
    return zoom;
}

void CameraSceneNode::setZoom(core::fs_float32 zoom)
{
    CameraSceneNode::zoom = zoom;
    transformation->setTransformUpdated(true);
}

const graphics::Window* CameraSceneNode::getWindow() const
{
    return window;
}

void CameraSceneNode::setWindow(const graphics::Window* window)
{
    CameraSceneNode::window = window;
    updateUniformData();
}

void CameraSceneNode::update(float deltaTime)
{
    if (transformation->isTransformUpdated() && active)
    {
        transformation->setTransformUpdated(false);
        updateUniformData();
    }
}

void CameraSceneNode::updateUniformData()
{
    const auto& position = transformation->getPosition();
    uniformData.view = glm::mat4(1.f);
    uniformData.projection = glm::ortho(position.x, position.x + window->getSize().x / zoom,
                                        position.y + window->getSize().y / zoom, position.y, -1.f, 1.f);
    uniformData.projection[1][1] *= -1;

    if (uniformBuffer->getMappedData() != nullptr)
    {
        memcpy(uniformBuffer->getMappedData(), &uniformData, sizeof(graphics::UniformData));
    }
}

}
