


#ifndef FIRESTORM_OBSTACLE_HPP
#define FIRESTORM_OBSTACLE_HPP

#include "scene/SpriteSceneNode.hpp"

#include <memory>

namespace fs::scene
{
class Obstacle : public SpriteSceneNode
{
public:
    Obstacle() = default;
    ~Obstacle() override = default;

    void
    create(io::InputManager& inputManager, const graphics::Sprite& sprite, physics::PhysicsManager& physicsManager);
    void destroy() override;

};

typedef std::unique_ptr<Obstacle> ObstaclePtr;
}

#endif //FIRESTORM_OBSTACLE_HPP
