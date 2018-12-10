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

#include "Alien.hpp"

namespace fs
{

void Alien::create(io::InputManager& inputManager, graphics::SpriteSheet& playerSpriteSheet, physics::PhysicsManager& physicsManager)
{
    Alien::playerSpriteSheet = &playerSpriteSheet;

    standingSprite = playerSpriteSheet.addSprite({67, 196, 66, 92});
    standingAnimation.push_back(standingSprite);

    jumpingAnimation.push_back(playerSpriteSheet.addSprite({438, 93, 67, 94}));

    createWalkingAnimation();

    startingPosition = {0.7f, -1.7f - 0.22f};

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {0.7f, -1.7f - 0.22f};

    b2PolygonShape shape;
    shape.SetAsBox(standingSprite->getWidthUnits() / 2.f, standingSprite->getHeightUnits() / 2.f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    PlayerSceneNode::create(inputManager, physicsManager, bodyDef, fixtureDef, standingAnimation, walkingAnimation, jumpingAnimation);
    setSpeedFps(10.f);
}

void Alien::destroy()
{
    playerSpriteSheet = nullptr;

    PlayerSceneNode::destroy();
}

void Alien::createWalkingAnimation()
{
    walkingAnimation.push_back(playerSpriteSheet->addSprite({0, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({73, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({146, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({0, 98, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({73, 98, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({146, 98, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({219, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({292, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({219, 98, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({365, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({292, 98, 72, 97}));
}

}
