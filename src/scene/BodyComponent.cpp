


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
