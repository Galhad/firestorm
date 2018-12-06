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

void Alien::create(graphics::SpriteSheet& playerSpriteSheet, physics::PhysicsManager& physicsManager)
{
    Alien::playerSpriteSheet = &playerSpriteSheet;

    standingSprite = playerSpriteSheet.addSprite({67, 196, 66, 92});
    standingAnimation.push_back(standingSprite);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {0.7f, -1.7f - 0.22f};

    PlayerSceneNode::create(standingAnimation, physicsManager, bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(standingSprite->getWidthUnits() / 2.f, standingSprite->getHeightUnits() / 2.f);

    body->CreateFixture(&shape, 0.0f);
}

void Alien::destroy()
{
    playerSpriteSheet = nullptr;

    PlayerSceneNode::destroy();
}
}
