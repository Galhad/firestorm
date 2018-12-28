// MIT License
//
// Copyright (c) 2018 Wojciech Wilk
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef FIRESTORM_PLAYERSCENENODE_HPP
#define FIRESTORM_PLAYERSCENENODE_HPP

#include "scene/AnimatedSpriteSceneNode.hpp"
#include "physics/PhysicsManager.hpp"

#include <memory>

namespace fs::scene
{
class PlayerSceneNode : public AnimatedSpriteSceneNode
{
public:
    PlayerSceneNode() = default;
    ~PlayerSceneNode() override = default;

    void create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                const b2FixtureDef& fixtureDef, const Animation& standingAnimation, const Animation& walkingAnimation,
                const Animation& jumpingAnimation);
    void destroy() override;

    void update(float deltaTimeMs) override;
    void physicsUpdate() override;

    void beginCollision(const BodyComponent& other) override;
    void endCollision(const BodyComponent& other) override;

    const core::Vector2f& getStartingPosition() const;
    void setStartingPosition(const core::Vector2f& startingPosition);

protected:
    void resetPosition();

protected:
    utils::LoggerPtr logger;

    core::fs_float32 speed = 1.5f;
    core::fs_float32 moving = 0.f;
    core::fs_float32 lastMoving = 0.f;

    bool inAir = false;
    bool lastInAir = false;

    core::fs_float32 jumpForce = 3.5f;
    bool jumping = false;

    core::fs_uint8 groundCollisions = 0;

    bool resettingPosition = false;

    core::Vector2f startingPosition;

    scene::AnimatedSpriteSceneNode::Animation standingAnimation;
    scene::AnimatedSpriteSceneNode::Animation walkingAnimation;
    scene::AnimatedSpriteSceneNode::Animation jumpingAnimation;

    core::fs_int32 coins = 0;

};

typedef std::unique_ptr<PlayerSceneNode> PlayerSceneNodePtr;
}

#endif //FIRESTORM_PLAYERSCENENODE_HPP
