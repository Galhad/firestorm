#ifndef FIRESTORM_ALIEN_HPP
#define FIRESTORM_ALIEN_HPP

#include "PlayerSceneNode.hpp"
#include <graphics/SpriteSheet.hpp>

#include <memory>

namespace fs
{
class Alien : public scene::PlayerSceneNode
{
public:
    Alien() = default;
    ~Alien() override = default;

    void create(io::InputManager& inputManager, graphics::SpriteSheet& playerSpriteSheet,
                physics::PhysicsManager& physicsManager, const core::Vector2f& startingPosition);
    void destroy() override;

private:
    void createWalkingAnimation();

protected:
    graphics::SpriteSheet* playerSpriteSheet = nullptr;
    graphics::Sprite* standingSprite = nullptr;

};

typedef std::unique_ptr<Alien> AlienPtr;
}

#endif //FIRESTORM_ALIEN_HPP
