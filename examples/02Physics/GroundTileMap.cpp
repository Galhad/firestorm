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

namespace fs::scene
{

void GroundTileMap::create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager,
                           const graphics::Sprite& leftSprite, const graphics::Sprite& midSprite,
                           const graphics::Sprite& rightSprite)
{
    core::Vector2i size{20, 20};
    core::Vector2f tileSize{leftSprite.getWidthUnits(), leftSprite.getHeightUnits()};

    TileMapSceneNode::create(inputManager, size, tileSize);
    setTileBuilderCallback([&](core::fs_int32 id) -> SceneNode*
                           {

                               const graphics::Sprite* sprite = nullptr;
                               if (id == leftId)
                               {
                                   sprite = &leftSprite;
                               }
                               else if (id == midId)
                               {
                                   sprite = &midSprite;
                               }
                               else if (id == rightId)
                               {
                                   sprite = &rightSprite;
                               }
                               else
                               {
                                   throw std::runtime_error("Undefined ground brick");
                               }

                               GroundBrick* groundBrick = nullptr;
                               groundBrick = new GroundBrick();
                               groundBrick->create(inputManager, *sprite, physicsManager);
                               return groundBrick;
                           });

    setTileId({0, 2}, leftId);
    setTileId({1, 2}, midId);
    setTileId({2, 2}, rightId);

    setTileId({4, 2}, leftId);
    setTileId({5, 2}, midId);
    setTileId({6, 2}, midId);
    setTileId({7, 2}, midId);
    setTileId({8, 2}, rightId);

    setTileId({6, 0}, leftId);
    setTileId({7, 0}, midId);
    setTileId({8, 0}, rightId);

    transformation->setPosition({0.f, -tileSize.y * 2.f});
}

void GroundTileMap::destroy()
{
    TileMapSceneNode::destroy();
}
}
