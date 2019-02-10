#include <iostream>
#include "ControlledCamera.hpp"

namespace fs
{

void ControlledCamera::create(io::InputManager& inputManager, const graphics::Window& window,
                              const graphics::MappedMemoryBuffer& uniformBuffer)
{
    CameraSceneNode::create(inputManager, window, uniformBuffer);
}

void ControlledCamera::destroy()
{
    CameraSceneNode::destroy();
}

void ControlledCamera::update(float deltaTime)
{
    float cameraOffset = cameraSpeed * deltaTime;

    core::Vector2f position = transformation->getPosition();
    if (inputManager->getKeyState(io::Key::Up) == io::KeyState::Pressed)
    {
        position.y += cameraOffset;
    }
    else if (inputManager->getKeyState(io::Key::Down) == io::KeyState::Pressed)
    {
        position.y -= cameraOffset;
    }
    if (inputManager->getKeyState(io::Key::Right) == io::KeyState::Pressed)
    {
        position.x += cameraOffset;
    }
    else if (inputManager->getKeyState(io::Key::Left) == io::KeyState::Pressed)
    {
        position.x -= cameraOffset;
    }
    if (transformation->getPosition() != position)
    {
        transformation->setPosition(position);
    }

    if (inputManager->getButtonState(io::Button::Left) == io::KeyState::Pressed)
    {
        setZoom(getZoom() + cameraOffset);
    }
    else if (inputManager->getButtonState(io::Button::Right) == io::KeyState::Pressed)
    {
        setZoom(getZoom() - cameraOffset);
    }

    CameraSceneNode::update(deltaTime);
}
}
