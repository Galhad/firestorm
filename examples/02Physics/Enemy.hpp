#ifndef FIRESTORM_ENEMY_HPP
#define FIRESTORM_ENEMY_HPP

#include "scene/AnimatedSpriteSceneNode.hpp"
#include "graphics/SpriteSheet.hpp"

#include <memory>

namespace fs::scene
{
class Enemy : public AnimatedSpriteSceneNode
{
public:
    Enemy() = default;
    ~Enemy() override = default;

    void create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                const b2FixtureDef& fixtureDef, const Animation& walkingAnimation);
    void destroy() override;

    const core::Vector2f& getStartingPosition() const;
    void setStartingPosition(const core::Vector2f& startingPosition);

protected:
    utils::LoggerPtr logger;
    core::Vector2f startingPosition;

    scene::AnimatedSpriteSceneNode::Animation walkingAnimation;

};

typedef std::unique_ptr<Enemy> EnemyPtr;
}

#endif //FIRESTORM_ENEMY_HPP
