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

#include "GroundBrick.hpp"

namespace fs::scene
{
void GroundBrick::create(const graphics::Sprite& sprite, physics::PhysicsManager& physicsManager)
{
    SpriteSceneNode::create(sprite);

    GroundBrick::physicsManager = &physicsManager;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;

    body = physicsManager.getWorld()->CreateBody(&bodyDef);

    core::fs_float32 halfWidth = sprite.getWidthUnits() / 2.f;
    core::fs_float32 halfHeight = sprite.getHeightUnits() / 2.f;

    b2EdgeShape shape;
    shape.Set(b2Vec2(-halfWidth / 2.f, -halfHeight), b2Vec2(halfWidth, -halfHeight));

    body->CreateFixture(&shape, 1.0f);

    bodyComponent = std::make_unique<BodyComponent>();
    bodyComponent->create(*transformation, *body);

    SceneNode::body = bodyComponent.get();
}

void GroundBrick::destroy()
{
    physicsManager->getWorld()->DestroyBody(body);
    body = nullptr;

    physicsManager = nullptr;

    SpriteSceneNode::destroy();
}
}
