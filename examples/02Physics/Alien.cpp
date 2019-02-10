#include "Alien.hpp"

namespace fs
{

void Alien::create(io::InputManager& inputManager, graphics::SpriteSheet& playerSpriteSheet,
                   physics::PhysicsManager& physicsManager, const core::Vector2f& startingPosition)
{
    Alien::playerSpriteSheet = &playerSpriteSheet;

    standingSprite = playerSpriteSheet.addSprite({67, 196, 66, 92});
    standingAnimation.push_back(standingSprite);

    jumpingAnimation.push_back(playerSpriteSheet.addSprite({438, 93, 67, 94}));

    createWalkingAnimation();

    Alien::startingPosition = startingPosition;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {startingPosition.x, startingPosition.y};

    b2PolygonShape shape;
    shape.SetAsBox(standingSprite->getWidthUnits() / 2.f, standingSprite->getHeightUnits() / 2.f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.restitution = 0.f;

    PlayerSceneNode::create(inputManager, physicsManager, bodyDef, fixtureDef, standingAnimation, walkingAnimation,
                            jumpingAnimation);
    setSpeedFps(10.f);
}

void Alien::destroy()
{
    playerSpriteSheet = nullptr;

    PlayerSceneNode::destroy();
}

void Alien::createWalkingAnimation()
{
    walkingAnimation.push_back(playerSpriteSheet->addSprite({0, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({73, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({146, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({0, 98, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({73, 98, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({146, 98, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({219, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({292, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({219, 98, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({365, 0, 72, 97}));
    walkingAnimation.push_back(playerSpriteSheet->addSprite({292, 98, 72, 97}));
}

}
