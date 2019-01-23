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
    windowCreationParams.windowTitle = "01SimpleApplication";
    engineCreationParams.windowCreationParams = windowCreationParams;

    graphics::GraphicsCreationParams graphicsCreationParams;
    graphicsCreationParams.applicationName = "01SimpleApplication";
#ifdef DEBUG
    graphicsCreationParams.enableValidationLayers = true;
#endif
    engineCreationParams.graphicsCreationParams = graphicsCreationParams;

    create(engineCreationParams);

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
    playerStandSprite = playerSpriteSheet->addSprite({0, 196, 66, 92});

    bgSceneNode.create(*inputManager, *bgSprite);
    bgSceneNode.getTransformation().setPosition({0.f, 0.f});
    bgSceneNode.getTransformation().setLayer(-0.1f);
    bgSceneNode.getTransformation().setScale(10.f, 10.f);
    scene->getNodes().push_back(&bgSceneNode);

    grassLeftSceneNode.create(*inputManager, *grassLeftSprite);
    scene->getNodes().push_back(&grassLeftSceneNode);

    grassMidSceneNode.create(*inputManager, *grassMidSprite);
    grassMidSceneNode.getTransformation().setPosition({0.7f, 0.f});
    scene->getNodes().push_back(&grassMidSceneNode);

    grassRightSceneNode.create(*inputManager, *grassRightSprite);
    grassRightSceneNode.getTransformation().setPosition({1.4f, 0.f});
    scene->getNodes().push_back(&grassRightSceneNode);

    playerSceneNode.create(*inputManager, *playerStandSprite);
    playerSceneNode.getTransformation().setPosition({0.7f, -0.7f - 0.22f});
    scene->getNodes().push_back(&playerSceneNode);

    sceneManager->setActiveScene(scene);

    camera.create(*inputManager, graphicsManager->getWindow(), vulkanDriver.getUniformBuffer());
    scene->getNodes().push_back(&camera);
    scene->setActiveCamera(&camera);
}

SimpleApplication::~SimpleApplication()
{

}

void SimpleApplication::update(float deltaTime)
{
    constexpr float rotationSpeed = 36.0f;
    auto rotation = bgSceneNode.getTransformation().getRotation();
    rotation.z += rotationSpeed * deltaTime;
    bgSceneNode.getTransformation().setRotation(rotation);

}

}