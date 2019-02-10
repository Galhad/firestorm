


#include "LevelEnd.hpp"
#include "Labels.hpp"

namespace fs::scene
{
void LevelEnd::create(io::InputManager& inputManager, fs::physics::PhysicsManager& physicsManager,
                      const core::Vector2f& point1,
                      const core::Vector2f& point2)
{
    SceneNode::create(inputManager);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;

    b2EdgeShape shape;
    shape.Set(b2Vec2(point1.x, point1.y), b2Vec2(point2.x, point2.y));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    createBodyComponent(physicsManager, bodyDef, fixtureDef);

    labels.insert(LABEL_LEVEL_END);
}

void LevelEnd::destroy()
{
    SceneNode::destroy();
}
}
