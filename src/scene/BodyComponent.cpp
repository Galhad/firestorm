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

#include <functional>
#include "BodyComponent.hpp"

namespace fs::scene
{
void BodyComponent::create(SceneNode& sceneNode, physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                           const b2FixtureDef& fixtureDef)
{
    Component::create(sceneNode);

    BodyComponent::transformation = &sceneNode.getTransformation();
    BodyComponent::physicsManager = &physicsManager;

    body = physicsManager.getWorld()->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
    body->SetUserData(this);

    beginCollisionCallback = nullptr;
    endCollisionCallback = nullptr;
}

void BodyComponent::destroy()
{
    beginCollisionCallback = nullptr;
    endCollisionCallback = nullptr;

    physicsManager->getWorld()->DestroyBody(body);
    body = nullptr;
    transformation = nullptr;
    physicsManager = nullptr;
    Component::destroy();
}

void BodyComponent::beginCollision(const BodyComponent& other) const
{
    if (beginCollisionCallback != nullptr)
    {
        (*beginCollisionCallback)(other);
    }
    sceneNode->beginCollision(other);
}

void BodyComponent::endCollision(const BodyComponent& other) const
{
    if (endCollisionCallback != nullptr)
    {
        (*endCollisionCallback)(other);
    }
    sceneNode->endCollision(other);
}

void BodyComponent::setBeginCollisionCallback(const CollisionCallback& beginCollisionCallback)
{
    BodyComponent::beginCollisionCallback = &beginCollisionCallback;
}

void BodyComponent::setEndCollisionCallback(const CollisionCallback& endCollisionCallback)
{
    BodyComponent::endCollisionCallback = &endCollisionCallback;
}

void BodyComponent::applyPhysicsStep()
{
    const auto& simulatedPosition = body->GetPosition();
    auto simulatedRotation = body->GetAngle();

    transformation->setPosition(simulatedPosition.x, simulatedPosition.y);
    transformation->setRotation(simulatedRotation);
}

b2Body* BodyComponent::getBody()
{
    return body;
}

}
