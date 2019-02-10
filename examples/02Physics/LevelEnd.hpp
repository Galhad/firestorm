


#ifndef FIRESTORM_LEVELEND_HPP
#define FIRESTORM_LEVELEND_HPP

#include "scene/SceneNode.hpp"

#include <memory>

namespace fs::scene
{
class LevelEnd : public SceneNode
{
public:
    LevelEnd() = default;
    ~LevelEnd() override = default;

    void create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager, const core::Vector2f& point1,
                const core::Vector2f& point2);
    void destroy() override;

};

typedef std::unique_ptr<LevelEnd> LevelEndPtr;
}

#endif //FIRESTORM_LEVELEND_HPP
