


#ifndef FIRESTORM_SLIME_HPP
#define FIRESTORM_SLIME_HPP

#include "Enemy.hpp"

#include <memory>

namespace fs::scene
{
class Slime : public Enemy
{
public:
    Slime() = default;
    ~Slime() override = default;

    void create(io::InputManager& inputManager, graphics::SpriteSheet& enemiesSpriteSheet,
                physics::PhysicsManager& physicsManager, const core::Vector2f& position);
    void destroy() override;

    void update(float deltaTime) override;
    void physicsUpdate() override;

protected:
    core::fs_float32 boundary = 0.7f;
    core::fs_float32 movementSpeed = 2.f;
    core::fs_float32 movementDirection = -1.f;

    void setMovement(core::fs_float32 movement) const;
};

typedef std::unique_ptr<Slime> SlimePtr;
}

#endif //FIRESTORM_SLIME_HPP
