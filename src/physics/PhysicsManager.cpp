


#include "PhysicsManager.hpp"
#include "scene/BodyComponent.hpp"

namespace fs::physics
{

void PhysicsManager::create(const PhysicsCreationParams& creationParams)
{
    world = std::make_unique<b2World>(b2Vec2(creationParams.gravity.x, creationParams.gravity.y));
    world->SetContactListener(this);

    timeStep = creationParams.timeStep;
    velocityIterations = creationParams.velocityIterations;
    positionIterations = creationParams.positionIterations;
}

void PhysicsManager::destroy()
{
    velocityIterations = 0;
    positionIterations = 0;
    timeStep = 0;

    world = nullptr;
}

void PhysicsManager::step(core::fs_int32 times)
{
    world->Step(timeStep * times, velocityIterations, positionIterations);
}

const b2World* PhysicsManager::getWorld() const
{
    return world.get();
}

b2World* PhysicsManager::getWorld()
{
    return world.get();
}

core::fs_float32 PhysicsManager::getTimeStep() const
{
    return timeStep;
}

void PhysicsManager::setTimeStep(core::fs_float32 timeStep)
{
    PhysicsManager::timeStep = timeStep;
}

void PhysicsManager::BeginContact(b2Contact* contact)
{
    auto* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyUserDataA != nullptr && bodyUserDataB != nullptr)
    {
        auto* bodyComponentA = static_cast<scene::BodyComponent*>(bodyUserDataA);
        auto* bodyComponentB = static_cast<scene::BodyComponent*>(bodyUserDataB);

        bodyComponentA->beginCollision(*bodyComponentB);
        bodyComponentB->beginCollision(*bodyComponentA);
    }
}

void PhysicsManager::EndContact(b2Contact* contact)
{
    auto* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyUserDataA != nullptr && bodyUserDataB != nullptr)
    {
        auto* bodyComponentA = static_cast<scene::BodyComponent*>(bodyUserDataA);
        auto* bodyComponentB = static_cast<scene::BodyComponent*>(bodyUserDataB);

        bodyComponentA->endCollision(*bodyComponentB);
        bodyComponentB->endCollision(*bodyComponentA);
    }
}

}
