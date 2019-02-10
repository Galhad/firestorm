


#include <iostream>
#include "PlayerSceneNode.hpp"
#include "Labels.hpp"

namespace fs::scene
{
void PlayerSceneNode::create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager,
                             const b2BodyDef& bodyDef,
                             const b2FixtureDef& fixtureDef, const Animation& standingAnimation,
                             const Animation& walkingAnimation,
                             const Animation& jumpingAnimation)
{
    AnimatedSpriteSceneNode::create(inputManager, standingAnimation);

    logger = spdlog::get(utils::CONSOLE_LOGGER_NAME);

    PlayerSceneNode::standingAnimation = standingAnimation;
    PlayerSceneNode::walkingAnimation = walkingAnimation;
    PlayerSceneNode::jumpingAnimation = jumpingAnimation;

    createBodyComponent(physicsManager, bodyDef, fixtureDef);

    transformation->setLayer(0.1f);

    labels.insert(LABEL_PLAYER);

    coins = 0;
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

    auto rotation = transformation->getRotation();
    rotation.y = moving < 0.f ? 180.f : 0.f;
    transformation->setRotation(rotation);

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

    if (!lastInAir && inAir)
    {
        setAnimation(jumpingAnimation);
    }
    else if (lastInAir && !inAir)
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

        if (groundCollisions > 0)
        {
            inAir = false;
        }
    }
    else if (labels.find(LABEL_COLLECTABLE) != labels.end())
    {
        ++coins;
        logger->info("Collected coin, total coins: {}", coins);
    }
    else if (labels.find(LABEL_ENEMY) != labels.end())
    {
        resettingPosition = true;
        logger->info("Enemy have killed player");
    }
}

void PlayerSceneNode::endCollision(const BodyComponent& other)
{
    const auto& labels = other.getSceneNode()->getLabels();

    if (labels.find(LABEL_GROUND) != labels.end())
    {
        --groundCollisions;

        if (groundCollisions == 0)
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

const core::Vector2f& PlayerSceneNode::getStartingPosition() const
{
    return startingPosition;
}

void PlayerSceneNode::setStartingPosition(const core::Vector2f& startingPosition)
{
    PlayerSceneNode::startingPosition = startingPosition;
}

}
