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

#include "PlayerSceneNode.hpp"

namespace fs::scene
{
void PlayerSceneNode::create(const fs::scene::AnimatedSpriteSceneNode::Animation& animation,
                             fs::physics::PhysicsManager& physicsManager,
                             const b2BodyDef& bodyDef)
{
    AnimatedSpriteSceneNode::create(animation);

    PlayerSceneNode::physicsManager = &physicsManager;

    body = physicsManager.getWorld()->CreateBody(&bodyDef);

    bodyComponent = std::make_unique<BodyComponent>();
    bodyComponent->create(*transformation, *body);

    SceneNode::body = bodyComponent.get();
}

void PlayerSceneNode::destroy()
{
    physicsManager->getWorld()->DestroyBody(body);
    body = nullptr;

    physicsManager = nullptr;

    AnimatedSpriteSceneNode::destroy();
}

void PlayerSceneNode::move(core::fs_float32 direction)
{
    moving = direction;
}

void PlayerSceneNode::physicsUpdate()
{
    auto velocity = body->GetLinearVelocity();
    velocity.x = moving * speed;
    body->SetLinearVelocity(velocity);

    if (jumping)
    {
        body->ApplyLinearImpulse(b2Vec2(0.f, -jumpForce), body->GetWorldCenter(), true);
        jumping  = false;
    }
}

void PlayerSceneNode::jump()
{
    jumping = true;
}
}
