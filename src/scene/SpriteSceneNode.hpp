


#ifndef FIRESTORM_SPRITESCENENODE_HPP
#define FIRESTORM_SPRITESCENENODE_HPP

#include "SceneNode.hpp"
#include "SpriteRendererComponent.hpp"

#include <memory>

namespace fs::scene
{
class SpriteSceneNode : public SceneNode
{
public:
    SpriteSceneNode() = default;
    ~SpriteSceneNode() override = default;

    void create(io::InputManager& inputManager, const graphics::Sprite& sprite);
    void destroy() override;

};

typedef std::unique_ptr<SpriteSceneNode> SpriteSceneNodePtr;
}

#endif //FIRESTORM_SPRITESCENENODE_HPP
