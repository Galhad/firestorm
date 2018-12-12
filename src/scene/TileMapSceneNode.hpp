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

#ifndef FIRESTORM_TILEMAPSCENENODE_HPP
#define FIRESTORM_TILEMAPSCENENODE_HPP

#include "Tile.hpp"

#include <memory>
#include <map>

namespace fs::scene
{
class TileMapSceneNode : public SceneNode
{
public:
    using CreateSceneNodeCallback = std::function<SceneNode*(core::fs_int32 id)>;

    void updateTilesPosition();
public:
    TileMapSceneNode() = default;
    ~TileMapSceneNode() override = default;

    void create(io::InputManager& inputManager, const core::Vector2i& size, const core::Vector2f& tileSize);
    void destroy() override;

    const std::vector<std::vector<Tile>>& getTiles() const;
    std::vector<std::vector<Tile>>& getTiles();

    Tile& getTile(const core::Vector2i& position);

    core::fs_int32 getTileId(const core::Vector2i& position) const;
    void setTileId(const core::Vector2i& position, core::fs_int32 tileId);
    void setTileId(const std::vector<core::Vector2i>& positions, core::fs_int32 tileId);

    const core::Vector2i& getSize() const;
    void setSize(const core::Vector2i& size);

    const core::Vector2f& getTileSize() const;
    void setTileSize(const core::Vector2f& tileSize);

    void setTileBuilderCallback(const CreateSceneNodeCallback& callback);

    bool isTilesChanged() const;
    void setTilesChanged(bool tilesChanged);

    void buildTiles();

    void update(float deltaTime) override;
    void physicsUpdate() override;
    void applyPhysicsStep() override;

protected:
    void resize(const core::Vector2i& size);

protected:
    std::vector<std::vector<Tile>> tiles;

//    std::map<core::fs_int32, CreateSceneNodeCallback> builderMapping;
    CreateSceneNodeCallback builderCallback;

    core::Vector2i size;
    core::Vector2f tileSize;

    bool tilesChanged = false;
};

typedef std::unique_ptr<TileMapSceneNode> TileMapSceneNodePtr;
}

#endif //FIRESTORM_TILEMAPSCENENODE_HPP
