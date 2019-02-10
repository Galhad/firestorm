#ifndef FIRESTORM_COLLECTABLE_HPP
#define FIRESTORM_COLLECTABLE_HPP

#include "scene/SpriteSceneNode.hpp"

#include <memory>

namespace fs::scene
{
class Collectable : public SpriteSceneNode
{
public:
    Collectable() = default;
    ~Collectable() override = default;

    void
    create(io::InputManager& inputManager, const graphics::Sprite& sprite, physics::PhysicsManager& physicsManager);
    void destroy() override;

    void beginCollision(const BodyComponent& other) override;

    void update(float deltaTime) override;

protected:
    bool shouldBeDestroyed = false;

};

typedef std::unique_ptr<Collectable> CollectablePtr;
}

#endif //FIRESTORM_COLLECTABLE_HPP
