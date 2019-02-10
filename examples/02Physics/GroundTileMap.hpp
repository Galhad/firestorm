#ifndef FIRESTORM_GROUNDTILEMAP_HPP
#define FIRESTORM_GROUNDTILEMAP_HPP

#include "GroundBrick.hpp"
#include "graphics/SpriteSheet.hpp"
#include "scene/TileMapSceneNode.hpp"
#include "scene/Scene.hpp"

#include <memory>

namespace fs::scene
{
class GroundTileMap : public TileMapSceneNode
{
public:
    GroundTileMap() = default;
    ~GroundTileMap() override = default;

    void create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager,
                graphics::SpriteSheet& tilesSpriteSheet, graphics::SpriteSheet& itemsSpriteSheet);
    void destroy() override;

protected:
    const core::fs_int32 leftId = 0;
    const core::fs_int32 midId = 1;
    const core::fs_int32 rightId = 2;
    const core::fs_int32 plantId = 3;
    const core::fs_int32 weightId = 4;
    const core::fs_int32 coinId = 5;

    graphics::SpriteSheet* tilesSpriteSheet = nullptr;
    graphics::Sprite* grassLeftSprite = nullptr;
    graphics::Sprite* grassMidSprite = nullptr;
    graphics::Sprite* grassRightSprite = nullptr;

    graphics::SpriteSheet* itemsSpriteSheet = nullptr;
    graphics::Sprite* plantSprite = nullptr;
    graphics::Sprite* cactusSprite = nullptr;
    graphics::Sprite* weightSprite = nullptr;
    graphics::Sprite* coinSprite = nullptr;


    void createSprites();
    GroundBrick* createGroundBrick(const graphics::Sprite* sprite, physics::PhysicsManager& physicsManager) const;
    void setTilesIds(const std::vector<std::vector<core::fs_int32>>& vector);
};

typedef std::unique_ptr<GroundTileMap> GroundTileMapPtr;
}

#endif //FIRESTORM_GROUNDTILEMAP_HPP
