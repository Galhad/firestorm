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
