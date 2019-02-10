


#include "SpriteSceneNode.hpp"

namespace fs::scene
{

void SpriteSceneNode::create(io::InputManager& inputManager, const graphics::Sprite& sprite)
{
    SceneNode::create(inputManager);

    renderer = std::make_unique<SpriteRendererComponent>();
    dynamic_cast<SpriteRendererComponent*>(renderer.get())->create(*this, *transformation, sprite);
}

void SpriteSceneNode::destroy()
{
    SceneNode::destroy();
}

}
