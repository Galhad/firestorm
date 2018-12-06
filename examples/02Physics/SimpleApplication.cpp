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
    EngineCreationParams engineCreationParams{};
    engineCreationParams.loggingLevel = spdlog::level::debug;

    graphics::WindowCreationParams windowCreationParams;
    windowCreationParams.windowTitle = "02Physics";
    engineCreationParams.windowCreationParams = windowCreationParams;

    graphics::GraphicsCreationParams graphicsCreationParams;
    graphicsCreationParams.applicationName = "02Physics";
    graphicsCreationParams.enableValidationLayers = true;
    engineCreationParams.graphicsCreationParams = graphicsCreationParams;

    create(engineCreationParams);

    auto textureResource = fileProvider->loadFile("../resources/texture.png");
    auto spritesheetResource = fileProvider->loadFile("../resources/tiles_spritesheet.png");
    auto bgResource = fileProvider->loadFile("../resources/bg.png");
    auto playerResource = fileProvider->loadFile("../resources/p1_spritesheet.png");

    auto& vulkanDriver = graphicsManager->getVulkanDriver();

    scene = sceneManager->createScene();
    scene->create();

    bgSpriteSheet = graphicsManager->createSpriteSheet(bgResource);
    bgSprite = bgSpriteSheet->addSprite({0, 0, bgSpriteSheet->getWidthPixels(), bgSpriteSheet->getHeightPixels()});

    tilesSpriteSheet = graphicsManager->createSpriteSheet(spritesheetResource);
    grassLeftSprite = tilesSpriteSheet->addSprite({504, 648, 70, 70});
    grassMidSprite = tilesSpriteSheet->addSprite({504, 576, 70, 70});
    grassRightSprite = tilesSpriteSheet->addSprite({504, 504, 70, 70});

    playerSpriteSheet = graphicsManager->createSpriteSheet(playerResource);

    bgSceneNode.create(*bgSprite);
    bgSceneNode.getTransformation().setPosition({0.f, 0.f});
    bgSceneNode.getTransformation().setLayer(-0.1f);
    bgSceneNode.getTransformation().setScale(10.f, 10.f);
    scene->getNodes().push_back(&bgSceneNode);

    grassLeftSceneNode.create(*grassLeftSprite, *physicsManager);
    scene->getNodes().push_back(&grassLeftSceneNode);

    grassMidSceneNode.create(*grassMidSprite, *physicsManager);
    grassMidSceneNode.getBody()->getBody()->SetTransform({0.7f, 0.f}, 0.f);
    scene->getNodes().push_back(&grassMidSceneNode);

    grassRightSceneNode.create(*grassRightSprite, *physicsManager);
    grassRightSceneNode.getBody()->getBody()->SetTransform({1.4f, 0.f}, 0.f);
    scene->getNodes().push_back(&grassRightSceneNode);

    playerSceneNode.create(*playerSpriteSheet, *physicsManager);
    scene->getNodes().push_back(&playerSceneNode);

    sceneManager->setActiveScene(scene);

    camera.create(graphicsManager->getWindow(), vulkanDriver.getUniformBuffer());
    camera.getTransformation().setPosition(-9.2f, -5.2f);
    camera.setZoom(41.5f);
    scene->getNodes().push_back(&camera);
    scene->setActiveCamera(&camera);
}

SimpleApplication::~SimpleApplication()
{

}

void SimpleApplication::update(float deltaTime)
{
    constexpr float cameraSpeed = 10.f;
    float cameraOffset = cameraSpeed * deltaTime;

    core::Vector2f cameraPosition = camera.getTransformation().getPosition();
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
    if (camera.getTransformation().getPosition() != cameraPosition)
    {
        camera.getTransformation().setPosition(cameraPosition);
    }

    if (inputManager->getKeyState(io::Key::A) == io::KeyState::Pressed)
    {
        playerSceneNode.move(-1.f);
    }
    else if (inputManager->getKeyState(io::Key::D) == io::KeyState::Pressed)
    {
        playerSceneNode.move(1.f);
    }
    else
    {
        playerSceneNode.move(0.f);
    }

    if (inputManager->getKeyState(io::Key::W) == io::KeyState::Pressed)
    {
        playerSceneNode.jump();
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