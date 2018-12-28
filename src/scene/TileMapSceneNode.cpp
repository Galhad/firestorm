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

#include "TileMapSceneNode.hpp"
#include "TileMapRendererComponent.hpp"

#include <stdexcept>

namespace fs::scene
{
void
TileMapSceneNode::create(io::InputManager& inputManager, const core::Vector2i& size, const core::Vector2f& tileSize)
{
    SceneNode::create(inputManager);
    TileMapSceneNode::size = size;
    TileMapSceneNode::tileSize = tileSize;

    resize(size);

    tilesChanged = false;

    renderer = std::make_unique<TileMapRendererComponent>();
    dynamic_cast<TileMapRendererComponent*>(renderer.get())->create(*this, *transformation);
}

void TileMapSceneNode::destroy()
{
//    builderMapping.clear();
    builderCallback = {};
    tiles.clear();

    SceneNode::destroy();
}

const core::Vector2i& TileMapSceneNode::getSize() const
{
    return size;
}

void TileMapSceneNode::setSize(const core::Vector2i& size)
{
    TileMapSceneNode::size = size;
    resize(size);
}

const core::Vector2f& TileMapSceneNode::getTileSize() const
{
    return tileSize;
}

void TileMapSceneNode::setTileSize(const core::Vector2f& tileSize)
{
    TileMapSceneNode::tileSize = tileSize;
}

Tile& TileMapSceneNode::getTile(const core::Vector2i& position)
{
    return tiles[position.x][position.y];
}

core::fs_int32 TileMapSceneNode::getTileId(const core::Vector2i& position) const
{
    return tiles[position.x][position.y].getId();
}

void TileMapSceneNode::setTileId(const core::Vector2i& position, core::fs_int32 tileId)
{
    tiles[position.x][position.y].setId(tileId);
    tilesChanged = true;
}

void TileMapSceneNode::setTileId(const std::vector<core::Vector2i>& positions, core::fs_int32 tileId)
{
    for (const auto& position : positions)
    {
        setTileId(position, tileId);
    }
    tilesChanged = true;
}

void
TileMapSceneNode::setTileBuilderCallback(const TileMapSceneNode::CreateSceneNodeCallback& callback)
{
    builderCallback = callback;
}

void TileMapSceneNode::buildTiles()
{
    for (auto& tilesColumn : tiles)
    {
        for (auto& tile : tilesColumn)
        {
            auto id = tile.getId();
            if (id < 0)
            {
                continue;
            }

            SceneNode* sceneNode = builderCallback(id);
            tile.setSceneNode(sceneNode);
        }
    }

    tilesChanged = false;
}

const std::vector<std::vector<Tile>>& TileMapSceneNode::getTiles() const
{
    return tiles;
}

std::vector<std::vector<Tile>>& TileMapSceneNode::getTiles()
{
    return tiles;
}

bool TileMapSceneNode::isTilesChanged() const
{
    return tilesChanged;
}

void TileMapSceneNode::setTilesChanged(bool tilesChanged)
{
    TileMapSceneNode::tilesChanged = tilesChanged;
}

void TileMapSceneNode::resize(const core::Vector2i& size)
{
    tiles.resize(size.x);
    for (auto& tile : tiles)
    {
        tile.resize(size.y);
    }
}

void TileMapSceneNode::updateTilesPosition()
{
    for (int x = 0; x < tiles.size(); x++)
    {
        for (int y = 0; y < tiles[x].size(); y++)
        {
            auto sceneNode = tiles[x][y].getSceneNode();
            if (sceneNode == nullptr)
            {
                continue;
            }

            core::Vector2f tilePosition{transformation->getPosition().x + x * tileSize.x,
                                        transformation->getPosition().y + y * tileSize.y};

            if (sceneNode->getBody() != nullptr)
            {
                b2Vec2 position(tilePosition.x, tilePosition.y);
                sceneNode->getBody()->getBody()->SetTransform(position, 0.f);
            }
            else
            {
                sceneNode->getTransformation().setPosition(tilePosition);
            }
        }
    }

    transformation->setGeometryUpdated(false);
}

void TileMapSceneNode::update(float deltaTime)
{
    SceneNode::update(deltaTime);

    for (auto& tileColumn : tiles)
    {
        for (auto& tile : tileColumn)
        {
            auto* sceneNode = tile.getSceneNode();
            if (sceneNode != nullptr)
            {
                sceneNode->update(deltaTime);
            }
        }
    }
}

void TileMapSceneNode::physicsUpdate()
{
    SceneNode::physicsUpdate();

    for (auto& tileColumn : tiles)
    {
        for (auto& tile : tileColumn)
        {
            auto* sceneNode = tile.getSceneNode();
            if (sceneNode != nullptr)
            {
                sceneNode->physicsUpdate();
            }
        }
    }

}

void TileMapSceneNode::applyPhysicsStep()
{
    SceneNode::applyPhysicsStep();

    for (auto& tileColumn : tiles)
    {
        for (auto& tile : tileColumn)
        {
            auto* sceneNode = tile.getSceneNode();
            if (sceneNode != nullptr)
            {
                sceneNode->applyPhysicsStep();
            }
        }
    }
}

}
