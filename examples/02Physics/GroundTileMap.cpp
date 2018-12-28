// MIT License
//
// Copyright (c) 2018 Wojciech Wilk
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "GroundTileMap.hpp"
#include "Obstacle.hpp"
#include "Collectable.hpp"

namespace fs::scene
{

void GroundTileMap::create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager,
                           graphics::SpriteSheet& tilesSpriteSheet, graphics::SpriteSheet& itemsSpriteSheet)
{
    GroundTileMap::tilesSpriteSheet = &tilesSpriteSheet;
    GroundTileMap::itemsSpriteSheet = &itemsSpriteSheet;

    createSprites();

    core::Vector2i size{40, 20};
    core::Vector2f tileSize{grassLeftSprite->getWidthUnits(), grassLeftSprite->getHeightUnits()};

    TileMapSceneNode::create(inputManager, size, tileSize);
    setTileBuilderCallback([&](core::fs_int32 id) -> SceneNode*
                           {

                               const graphics::Sprite* sprite = nullptr;
                               if (id == leftId)
                               {
                                   return createGroundBrick(grassLeftSprite, physicsManager);
                               }
                               else if (id == midId)
                               {
                                   return createGroundBrick(grassMidSprite, physicsManager);
                               }
                               else if (id == rightId)
                               {
                                   return createGroundBrick(grassRightSprite, physicsManager);
                               }
                               else if (id == plantId)
                               {
                                   auto* spriteSceneNode = new SpriteSceneNode();
                                   spriteSceneNode->create(inputManager, *plantSprite);
                                   return spriteSceneNode;
                               }
                               else if (id == cactusId)
                               {
                                   return nullptr;
                               }
                               else if (id == weightId)
                               {
                                   auto* obstacleSceneNode = new Obstacle();
                                   obstacleSceneNode->create(inputManager, *weightSprite, physicsManager);
                                   return obstacleSceneNode;
                               }
                               else if (id == coinId)
                               {
                                   auto* collectableSceneNode = new Collectable();
                                   collectableSceneNode->create(inputManager, *coinSprite, physicsManager);
                                   return collectableSceneNode;
                               }
                               else
                               {
                                   throw std::runtime_error("Undefined ground brick");
                               }
                           });

    //@formatter:off
    std::vector<std::vector<core::fs_int32>> ids =
        {
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     plantId, -1,    coinId,  -1,    plantId, -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, leftId, midId,   midId, midId,   midId, midId,   rightId, -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, coinId, coinId, coinId,  -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, leftId, midId,  rightId, -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1,},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, coinId, plantId, coinId,  -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, leftId, midId,   rightId, -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      weightId, -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      leftId,  midId,    rightId, -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     plantId, coinId, plantId, -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, coinId, coinId, coinId,  coinId,  -1, -1,     coinId,  -1,    plantId, -1,    coinId,  -1,      plantId, -1,    -1,    weightId, coinId,  -1, -1, coinId, coinId, coinId, coinId},
            {leftId, midId, rightId, -1, leftId, midId,   midId,  midId,   rightId, -1,       -1,      -1, -1,     -1,      -1,      -1, -1, leftId, midId,  midId,   rightId, -1, -1,     leftId,  midId, midId,   midId, midId,   midId,   midId,   midId, midId, midId,    rightId, -1, -1, leftId, midId,  midId,  rightId},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1},
            {-1,     -1,    -1,      -1, -1,     -1,      -1,     -1,      -1,      -1,       -1,      -1, -1,     -1,      -1,      -1, -1, -1,     -1,     -1,      -1,      -1, -1,     -1,      -1,    -1,      -1,    -1,      -1,      -1,      -1,    -1,    -1,       -1,      -1, -1, -1,     -1,     -1,     -1}
        };
    //@formatter:on
    setTilesIds(ids);
}

GroundBrick*
GroundTileMap::createGroundBrick(const graphics::Sprite* sprite, physics::PhysicsManager& physicsManager) const
{
    auto* groundBrick = new GroundBrick();
    groundBrick->create(*inputManager, *sprite, physicsManager);
    return groundBrick;
}

void GroundTileMap::createSprites()
{
    grassLeftSprite = tilesSpriteSheet->addSprite({504, 648, 70, 70});
    grassMidSprite = tilesSpriteSheet->addSprite({504, 576, 70, 70});
    grassRightSprite = tilesSpriteSheet->addSprite({504, 504, 70, 70});
    plantSprite = itemsSpriteSheet->addSprite({0, 363, 70, 70});
    cactusSprite = itemsSpriteSheet->addSprite({360, 216, 70, 70});
    weightSprite = itemsSpriteSheet->addSprite({490, 144, 70, 70});
    coinSprite = itemsSpriteSheet->addSprite({288, 360, 70, 70});
}

void GroundTileMap::destroy()
{
    TileMapSceneNode::destroy();
}

void GroundTileMap::setTilesIds(const std::vector<std::vector<core::fs_int32>>& vector)
{
    for (core::fs_int64 y = 0; y < vector.size(); ++y)
    {
        for (core::fs_int64 x = 0; x < vector[y].size(); ++x)
        {
            setTileId(core::Vector2i{x, y}, vector[y][x]);
        }
    }
}
}
