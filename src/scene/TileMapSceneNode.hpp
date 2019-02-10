


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
    void updateTilesPosition();

    void update(float deltaTime) override;
    void physicsUpdate() override;
    void applyPhysicsStep() override;

protected:
    void resize(const core::Vector2i& size);

protected:
    std::vector<std::vector<Tile>> tiles;

    CreateSceneNodeCallback builderCallback;

    core::Vector2i size;
    core::Vector2f tileSize;

    bool tilesChanged = false;
};

typedef std::unique_ptr<TileMapSceneNode> TileMapSceneNodePtr;
}

#endif //FIRESTORM_TILEMAPSCENENODE_HPP
