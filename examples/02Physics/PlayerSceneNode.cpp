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

#include <iostream>
#include "PlayerSceneNode.hpp"
#include "Labels.hpp"

namespace fs::scene
{
void PlayerSceneNode::create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                             const b2FixtureDef& fixtureDef, const Animation& standingAnimation,
                             const Animation& walkingAnimation,
                             const Animation& jumpingAnimation)
{
    AnimatedSpriteSceneNode::create(inputManager, standingAnimation);

    PlayerSceneNode::standingAnimation = standingAnimation;
    PlayerSceneNode::walkingAnimation = walkingAnimation;
    PlayerSceneNode::jumpingAnimation = jumpingAnimation;

    createBodyComponent(physicsManager, bodyDef, fixtureDef);

    labels.insert(LABEL_PLAYER);
}

void PlayerSceneNode::destroy()
{
    AnimatedSpriteSceneNode::destroy();
}

void PlayerSceneNode::update(float deltaTimeMs)
{
    lastMoving = moving;
    if (inputManager->getKeyState(io::Key::A) == io::KeyState::Pressed)
    {
        moving = -1.f;
    }
    else if (inputManager->getKeyState(io::Key::D) == io::KeyState::Pressed)
    {
        moving = 1.f;
    }
    else
    {
        moving = 0.f;
    }

    if (inputManager->getKeyState(io::Key::W) == io::KeyState::Pressed)
    {
        jumping = true;
    }

    if (moving != lastMoving && groundCollisions > 0)
    {
        if (moving < 0.f || moving > 0.f)
        {
            setAnimation(walkingAnimation);
        }
        else
        {
            setAnimation(standingAnimation);
        }
    }

    if(!lastInAir && inAir)
    {
        setAnimation(jumpingAnimation);
    }
    else if(lastInAir && !inAir)
    {
        setAnimation(standingAnimation);
    }
    lastInAir = inAir;

    AnimatedSpriteSceneNode::update(deltaTimeMs);
}

void PlayerSceneNode::physicsUpdate()
{
    auto velocity = body->getBody()->GetLinearVelocity();
    velocity.x = moving * speed;
    body->getBody()->SetLinearVelocity(velocity);

    if (jumping && groundCollisions > 0)
    {
        body->getBody()->ApplyLinearImpulse(b2Vec2(0.f, -jumpForce), body->getBody()->GetWorldCenter(), true);
        jumping = false;
    }

    if (resettingPosition)
    {
        resetPosition();
        resettingPosition = false;
    }
}

void PlayerSceneNode::beginCollision(const BodyComponent& other)
{
    const auto& labels = other.getSceneNode()->getLabels();

    if (labels.find(LABEL_LEVEL_END) != labels.end())
    {
        resettingPosition = true;
    }
    else if (labels.find(LABEL_GROUND) != labels.end())
    {
        ++groundCollisions;

        if(groundCollisions > 0)
        {
            inAir = false;
        }
    }
}

void PlayerSceneNode::endCollision(const BodyComponent& other)
{
    const auto& labels = other.getSceneNode()->getLabels();

    if (labels.find(LABEL_GROUND) != labels.end())
    {
        --groundCollisions;

        if(groundCollisions == 0)
        {
            inAir = true;
        }
    }
}

void PlayerSceneNode::resetPosition()
{
    body->getBody()->SetLinearVelocity(b2Vec2(0.f, 0.f));
    jumping = false;

    body->getBody()->SetTransform(b2Vec2(startingPosition.x, startingPosition.y), 0.f);
}

}
