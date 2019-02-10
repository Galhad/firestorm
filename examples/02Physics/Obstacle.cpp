


#include "Obstacle.hpp"
#include "Labels.hpp"

namespace fs::scene
{

void Obstacle::create(io::InputManager& inputManager, const graphics::Sprite& sprite,
                      physics::PhysicsManager& physicsManager)
{
    SpriteSceneNode::create(inputManager, sprite);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;

    core::fs_float32 halfWidth = sprite.getWidthUnits() / 2.f;
    core::fs_float32 halfHeight = sprite.getHeightUnits() / 2.f;

    b2PolygonShape shape;
    shape.SetAsBox(halfWidth, halfHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.restitution = 0.f;

    createBodyComponent(physicsManager, bodyDef, fixtureDef);

    labels.insert(LABEL_OBSTACLE);
    labels.insert(LABEL_GROUND);
}

void Obstacle::destroy()
{
    SpriteSceneNode::destroy();
}
}
