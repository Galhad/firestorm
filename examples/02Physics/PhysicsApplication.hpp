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

#ifndef FIRESTORM_PHYSICSAPPLICATION_HPP
#define FIRESTORM_PHYSICSAPPLICATION_HPP

#include <Engine.hpp>

#include <scene/SpriteSceneNode.hpp>
#include <scene/AnimatedSpriteSceneNode.hpp>
#include <scene/CameraSceneNode.hpp>
#include "Alien.hpp"
#include "GroundBrick.hpp"
#include "LevelEnd.hpp"
#include "GroundTileMap.hpp"

#include <iostream>
#include <memory>

namespace fs
{
class PhysicsApplication : public fs::Engine
{
public:
    PhysicsApplication();
    ~PhysicsApplication() override;

    void update(float deltaTime) override;

private:
    void loadResources();

private:
    io::Resource spritesheetResource;
    io::Resource bgResource;
    io::Resource playerResource;

    scene::CameraSceneNode camera;
    scene::Scene* scene;

    graphics::SpriteSheet* bgSpriteSheet;
    graphics::Sprite* bgSprite;
    scene::SpriteSceneNode bgSceneNode;

    graphics::SpriteSheet* tilesSpriteSheet;
    graphics::Sprite* grassLeftSprite;
    graphics::Sprite* grassMidSprite;
    graphics::Sprite* grassRightSprite;

    scene::GroundTileMap groundTileMap;

    graphics::SpriteSheet* playerSpriteSheet = nullptr;
    Alien playerSceneNode;
    scene::LevelEnd levelEnd;
};

typedef std::unique_ptr<PhysicsApplication> SimpleApplicationPtr;
}

#endif //FIRESTORM_PHYSICSAPPLICATION_HPP