


#ifndef FIRESTORM_PHYSICSAPPLICATION_HPP
#define FIRESTORM_PHYSICSAPPLICATION_HPP

#include <Engine.hpp>

#include <scene/SpriteSceneNode.hpp>
#include <scene/AnimatedSpriteSceneNode.hpp>
#include <scene/CameraSceneNode.hpp>
#include "Alien.hpp"
#include "GroundBrick.hpp"
#include "LevelEnd.hpp"
#include "GroundTileMap.hpp"
#include "Slime.hpp"

#include <iostream>
#include <memory>

namespace fs
{
class PhysicsApplication : public fs::Engine
{
public:
    PhysicsApplication();
    ~PhysicsApplication() override;

private:
    void loadResources();
    void createBgSceneNode();
    void createLevelEndSceneNode();
    void createTileMap();
    void createPlayer();
    void createSlimes();

private:
    io::Resource spritesheetResource;
    io::Resource itemsResource;
    io::Resource bgResource;
    io::Resource playerResource;
    io::Resource enemiesResource;

    scene::CameraSceneNode camera;
    scene::Scene* scene;

    graphics::SpriteSheet* bgSpriteSheet;
    graphics::Sprite* bgSprite;
    scene::SpriteSceneNode bgSceneNode;

    graphics::SpriteSheet* tilesSpriteSheet;
    graphics::SpriteSheet* itemsSpriteSheet;
    graphics::SpriteSheet* enemiesSpriteSheet;

    scene::GroundTileMap groundTileMap;

    graphics::SpriteSheet* playerSpriteSheet = nullptr;
    Alien playerSceneNode;
    scene::LevelEnd levelEnd;
    scene::Slime slime1;
    scene::Slime slime2;
    scene::Slime slime3;
};

typedef std::unique_ptr<PhysicsApplication> SimpleApplicationPtr;
}

#endif //FIRESTORM_PHYSICSAPPLICATION_HPP
