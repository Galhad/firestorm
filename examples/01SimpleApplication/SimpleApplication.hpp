#ifndef FIRESTORM_SIMPLEAPPLICATION_HPP
#define FIRESTORM_SIMPLEAPPLICATION_HPP

#include <Engine.hpp>

#include "ControlledCamera.hpp"

#include <scene/SpriteSceneNode.hpp>
#include <scene/AnimatedSpriteSceneNode.hpp>
#include <scene/CameraSceneNode.hpp>
#include <iostream>
#include <memory>

namespace fs
{
class SimpleApplication : public fs::Engine
{
public:
    SimpleApplication();
    ~SimpleApplication() override;

    void update(float deltaTime) override;

private:
    ControlledCamera camera;
    scene::Scene* scene;

    graphics::SpriteSheet* bgSpriteSheet;
    graphics::Sprite* bgSprite;
    scene::SpriteSceneNode bgSceneNode;

    graphics::SpriteSheet* tilesSpriteSheet;
    graphics::Sprite* grassLeftSprite;
    graphics::Sprite* grassMidSprite;
    graphics::Sprite* grassRightSprite;
    scene::SpriteSceneNode grassLeftSceneNode;
    scene::SpriteSceneNode grassMidSceneNode;
    scene::SpriteSceneNode grassRightSceneNode;

    graphics::SpriteSheet* playerSpriteSheet;
    graphics::Sprite* playerStandSprite;
    scene::SpriteSceneNode playerSceneNode;

};

typedef std::unique_ptr<SimpleApplication> SimpleApplicationPtr;
}

#endif //FIRESTORM_SIMPLEAPPLICATION_HPP
