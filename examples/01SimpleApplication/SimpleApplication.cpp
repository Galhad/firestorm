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

#include "SimpleApplication.hpp"

namespace fs
{
SimpleApplication::SimpleApplication()
{
    graphics::WindowCreationParams windowCreationParams;
    windowCreationParams.windowTitle = "01SimpleApplication";

    graphics::GraphicsCreationParams graphicsCreationParams;
    graphicsCreationParams.applicationName = "01SimpleApplication";
    graphicsCreationParams.enableValidationLayers = true;

    create({windowCreationParams, graphicsCreationParams});

    auto textureResource = fileProvider->loadFile("../resources/texture.png");

    auto& vulkanDriver = graphicsManager->getVulkanDriver();

    scene = sceneManager->createScene();
    scene->create();

    spriteSheet = graphicsManager->createSpriteSheet(textureResource);
    sprite = spriteSheet->addSprite({0, 0, spriteSheet->getWidthPixels(), spriteSheet->getHeightPixels()});

    spriteSceneNode1.create(*sprite);
    spriteSceneNode1.setLayer(0.5f);
    scene->getNodes().push_back(&spriteSceneNode1);

    spriteSceneNode2.create(*sprite);
    spriteSceneNode2.setPosition({0.f, -1.5f});
    spriteSceneNode2.setLayer(0.0f);
    scene->getNodes().push_back(&spriteSceneNode2);

    sceneManager->setActiveScene(scene);

    camera.create(graphicsManager->getWindow(), vulkanDriver.getUniformBuffer());
    camera.setActive(true);
    scene->getNodes().push_back(&camera);
}

SimpleApplication::~SimpleApplication()
{

}

void SimpleApplication::update(float deltaTimeMs)
{
    std::cout << "delta time [ms]: " << deltaTimeMs << std::endl;
    constexpr float cameraSpeed = 0.001f;
    float cameraOffset = cameraSpeed * deltaTimeMs;

    core::Vector2f cameraPosition = camera.getPosition();
    if (inputManager->getKeyState(io::Key::Up) == io::KeyState::Pressed)
    {
        cameraPosition.y += cameraOffset;
    }
    else if (inputManager->getKeyState(io::Key::Down) == io::KeyState::Pressed)
    {
        cameraPosition.y -= cameraOffset;
    }
    if (inputManager->getKeyState(io::Key::Right) == io::KeyState::Pressed)
    {
        cameraPosition.x += cameraOffset;
    }
    else if (inputManager->getKeyState(io::Key::Left) == io::KeyState::Pressed)
    {
        cameraPosition.x -= cameraOffset;
    }
    if (camera.getPosition() != cameraPosition)
    {
        camera.setPosition(cameraPosition);
    }

    if (inputManager->getButtonState(io::Button::Left) == io::KeyState::Pressed)
    {
        camera.setZoom(camera.getZoom() + cameraOffset);
    }
    else if (inputManager->getButtonState(io::Button::Right) == io::KeyState::Pressed)
    {
        camera.setZoom(camera.getZoom() - cameraOffset);
    }
}

}
