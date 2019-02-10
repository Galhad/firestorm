#include "Enemy.hpp"
#include "Labels.hpp"

namespace fs::scene
{

void Enemy::create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                   const b2FixtureDef& fixtureDef, const Animation& walkingAnimation)
{
    AnimatedSpriteSceneNode::create(inputManager, walkingAnimation);

    logger = spdlog::get(utils::CONSOLE_LOGGER_NAME);

    Enemy::walkingAnimation = walkingAnimation;

    createBodyComponent(physicsManager, bodyDef, fixtureDef);

    transformation->setLayer(0.1f);

    labels.insert(LABEL_ENEMY);
}

void Enemy::destroy()
{
    AnimatedSpriteSceneNode::destroy();
}

const core::Vector2f& Enemy::getStartingPosition() const
{
    return startingPosition;
}

void Enemy::setStartingPosition(const core::Vector2f& startingPosition)
{
    Enemy::startingPosition = startingPosition;
}
}
