


#ifndef FIRESTORM_TILE_HPP
#define FIRESTORM_TILE_HPP

#include "SceneNode.hpp"

#include <memory>

namespace fs::scene
{
class Tile
{
public:
    Tile() = default;
    Tile(Tile&& other);
    virtual ~Tile() = default;

    void create(core::fs_int32 id, SceneNode* sceneNode);
    virtual void destroy();

    core::fs_int32 getId() const;
    void setId(core::fs_int32 id);

    SceneNode* getSceneNode();
    const SceneNode* getSceneNode() const;
    void setSceneNode(SceneNode* sceneNode);

protected:
    core::fs_int32 id = -1;
    SceneNodePtr sceneNode = nullptr;

};

typedef std::unique_ptr<Tile> TilePtr;

}

#endif //FIRESTORM_TILE_HPP
