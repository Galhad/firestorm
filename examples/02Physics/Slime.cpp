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

#include "Slime.hpp"

namespace fs::scene
{

void Slime::create(io::InputManager& inputManager, graphics::SpriteSheet& enemiesSpriteSheet,
                   physics::PhysicsManager& physicsManager, const core::Vector2f& position)
{

    auto* walkingSprite1 = enemiesSpriteSheet.addSprite({52, 125, 50, 28});
    walkingAnimation.push_back(walkingSprite1);
    walkingAnimation.push_back(enemiesSpriteSheet.addSprite({0, 125, 51, 26}));

    Slime::startingPosition = position;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {startingPosition.x, startingPosition.y};

    b2PolygonShape shape;
    shape.SetAsBox(walkingSprite1->getWidthUnits() / 2.f, walkingSprite1->getHeightUnits() / 2.f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.restitution = 0.f;

    Enemy::create(inputManager, physicsManager, bodyDef, fixtureDef, walkingAnimation);

    setSpeedFps(6.f);

    setMovement(movementSpeed);
}

void Slime::destroy()
{
    Enemy::destroy();
}

void Slime::update(float deltaTime)
{
    AnimatedSpriteSceneNode::update(deltaTime);
}

void Slime::physicsUpdate()
{
    if (body->getBody()->GetPosition().x <= startingPosition.x - boundary)
    {
        movementDirection = 1.f;
    }
    else if (body->getBody()->GetPosition().x >= startingPosition.x + boundary)
    {
        movementDirection = -1.f;
    }

    setMovement(movementSpeed * movementDirection);
}

void Slime::setMovement(core::fs_float32 movement) const
{
    auto rotation = transformation->getRotation();
    if (movement <= 0.f)
    {
        rotation.y = 0;
    }
    else
    {
        rotation.y = 180.f;
    }
    transformation->setRotation(rotation);

    body->getBody()->SetLinearVelocity({movement, body->getBody()->GetLinearVelocity().y});
}
}
