#ifndef FIRESTORM_GROUNDBRICK_HPP
#define FIRESTORM_GROUNDBRICK_HPP

#include "scene/SpriteSceneNode.hpp"
#include "physics/PhysicsManager.hpp"

#include <memory>

namespace fs::scene
{
class GroundBrick : public SpriteSceneNode
{
public:
    GroundBrick() = default;
    ~GroundBrick() override = default;

    void
    create(io::InputManager& inputManager, const graphics::Sprite& sprite, physics::PhysicsManager& physicsManager);
    void destroy() override;

protected:

};

typedef std::unique_ptr<GroundBrick> GroundBrickPtr;
}

#endif //FIRESTORM_GROUNDBRICK_HPP
