


#include "Tile.hpp"

namespace fs::scene
{
Tile::Tile(Tile&& other) : id(other.id), sceneNode(std::move(other.sceneNode))
{
}

void Tile::create(core::fs_int32 id, SceneNode* sceneNode)
{
    Tile::id = id;
    Tile::sceneNode = SceneNodePtr(sceneNode);
}

void Tile::destroy()
{
    sceneNode = nullptr;
    id = -1;
}

core::fs_int32 Tile::getId() const
{
    return id;
}

void Tile::setId(core::fs_int32 id)
{
    Tile::id = id;
}

SceneNode* Tile::getSceneNode()
{
    return sceneNode.get();
}

const SceneNode* Tile::getSceneNode() const
{
    return sceneNode.get();
}

void Tile::setSceneNode(SceneNode* sceneNode)
{
    Tile::sceneNode = SceneNodePtr(sceneNode);
}

}
