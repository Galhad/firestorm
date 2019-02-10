#include "Collectable.hpp"
#include "Labels.hpp"
#include "scene/Scene.hpp"

namespace fs::scene
{
void Collectable::create(io::InputManager& inputManager, const graphics::Sprite& sprite,
                         physics::PhysicsManager& physicsManager)
{
    SpriteSceneNode::create(inputManager, sprite);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;

    core::fs_float32 halfWidth = sprite.getWidthUnits() / 4.f;
    core::fs_float32 halfHeight = sprite.getHeightUnits() / 4.f;

    b2PolygonShape shape;
    shape.SetAsBox(halfWidth, halfHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.isSensor = true;

    createBodyComponent(physicsManager, bodyDef, fixtureDef);

    labels.insert(LABEL_COLLECTABLE);

    shouldBeDestroyed = false;
}

void Collectable::destroy()
{
    SpriteSceneNode::destroy();
}

void Collectable::beginCollision(const BodyComponent& other)
{
    const auto& labels = other.getSceneNode()->getLabels();
    if (labels.find(LABEL_PLAYER) != labels.end())
    {
        shouldBeDestroyed = true;
    }
}

void Collectable::update(float deltaTime)
{
    if (shouldBeDestroyed)
    {
        body->getBody()->SetActive(false);
        renderer->setActive(false);
    }
}
}
