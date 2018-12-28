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

#include "PhysicsApplication.hpp"

namespace fs
{
PhysicsApplication::PhysicsApplication()
{
    EngineCreationParams engineCreationParams{};
    engineCreationParams.loggingLevel = spdlog::level::debug;

    graphics::WindowCreationParams windowCreationParams;
    windowCreationParams.windowTitle = "02Physics";
    windowCreationParams.windowSize = {1280, 720};
    engineCreationParams.windowCreationParams = windowCreationParams;

    graphics::GraphicsCreationParams graphicsCreationParams;
    graphicsCreationParams.applicationName = "02Physics";
#ifdef DEBUG
    graphicsCreationParams.enableValidationLayers = true;
#endif
    engineCreationParams.graphicsCreationParams = graphicsCreationParams;

    create(engineCreationParams);

    loadResources();

    auto& vulkanDriver = graphicsManager->getVulkanDriver();

    scene = sceneManager->createScene();
    scene->create();

    bgSpriteSheet = graphicsManager->createSpriteSheet(bgResource);
    bgSprite = bgSpriteSheet->addSprite({0, 0, bgSpriteSheet->getWidthPixels(), bgSpriteSheet->getHeightPixels()});

    tilesSpriteSheet = graphicsManager->createSpriteSheet(spritesheetResource);
    itemsSpriteSheet = graphicsManager->createSpriteSheet(itemsResource);
    playerSpriteSheet = graphicsManager->createSpriteSheet(playerResource);
    enemiesSpriteSheet = graphicsManager->createSpriteSheet(enemiesResource);

    createBgSceneNode();
    createTileMap();
    createPlayer();
    createSlimes();
    createLevelEndSceneNode();

    sceneManager->setActiveScene(scene);

    camera.create(*inputManager, graphicsManager->getWindow(), vulkanDriver.getUniformBuffer());
    camera.getTransformation().setPosition(-1.2f, -14.2f);
    camera.setZoom(41.5f);
    scene->getNodes().push_back(&camera);
    scene->setActiveCamera(&camera);
}

void PhysicsApplication::createSlimes()
{
    slime1.create(*inputManager, *enemiesSpriteSheet, *physicsManager, {17.45f, 5.475f});
    scene->getNodes().push_back(&slime1);

    slime2.create(*inputManager, *enemiesSpriteSheet, *physicsManager, {17.45f, 11.075f});
    scene->getNodes().push_back(&slime2);

    slime3.create(*inputManager, *enemiesSpriteSheet, *physicsManager, {20.32f, 11.075f});
    scene->getNodes().push_back(&slime3);
}

void PhysicsApplication::createPlayer()
{
    core::Vector2f playerStartingPosition = {0.f, groundTileMap.getTileSize().y * 14};
    playerSceneNode.create(*inputManager, *playerSpriteSheet, *physicsManager, playerStartingPosition);
    scene->getNodes().push_back(&playerSceneNode);
}

void PhysicsApplication::createTileMap()
{
    groundTileMap.create(*inputManager, *physicsManager, *tilesSpriteSheet, *itemsSpriteSheet);
    scene->getNodes().push_back(&groundTileMap);
}

void PhysicsApplication::createLevelEndSceneNode()
{
    core::fs_float32 levelEndWidth = (groundTileMap.getTileSize().x + 2) * groundTileMap.getSize().x;
    core::fs_float32 halfLevelEndWidth = levelEndWidth / 2.f;

    core::fs_float32 levelEndY = groundTileMap.getTileSize().y * (groundTileMap.getSize().y + 2);

    core::Vector2f point1 = {-halfLevelEndWidth, levelEndY};
    core::Vector2f point2 = {halfLevelEndWidth, levelEndY};

    levelEnd.create(*inputManager, *physicsManager, point1, point2);
    scene->getNodes().push_back(&levelEnd);
}

void PhysicsApplication::createBgSceneNode()
{
    bgSceneNode.create(*inputManager, *bgSprite);

    core::Vector2f position = {-bgSprite->getWidthUnits() / 2.f, -bgSprite->getHeightUnits() / 2.f};
    core::Vector2f scale = {50.f, 50.f};

    bgSceneNode.getTransformation().setPosition(position);
    bgSceneNode.getTransformation().setLayer(-0.1f);
    bgSceneNode.getTransformation().setScale(scale);
    scene->getNodes().push_back(&bgSceneNode);
}

PhysicsApplication::~PhysicsApplication()
{

}

void PhysicsApplication::update(float deltaTime)
{
}

void PhysicsApplication::loadResources()
{
    auto spritesheetResourceFuture = fileProvider->loadFileAsync("../resources/tiles_spritesheet.png");
    auto itemsResourceFuture = fileProvider->loadFileAsync("../resources/items_spritesheet.png");
    auto bgResourceFuture = fileProvider->loadFileAsync("../resources/bg.png");
    auto playerResourceFuture = fileProvider->loadFileAsync("../resources/p1_spritesheet.png");
    auto enemiesResourceFuture = fileProvider->loadFileAsync("../resources/enemies_spritesheet.png");

    spritesheetResourceFuture.wait();
    itemsResourceFuture.wait();
    bgResourceFuture.wait();
    playerResourceFuture.wait();
    enemiesResourceFuture.wait();

    spritesheetResource = spritesheetResourceFuture.get();
    itemsResource = itemsResourceFuture.get();
    bgResource = bgResourceFuture.get();
    playerResource = playerResourceFuture.get();
    enemiesResource = enemiesResourceFuture.get();
}

}
