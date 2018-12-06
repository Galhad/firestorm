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

    void create(const Animation& animation, physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef);
    void destroy() override;

    void physicsUpdate() override;

    void move(core::fs_float32 direction);
    void jump();

protected:
    BodyComponentPtr bodyComponent = nullptr;
    physics::PhysicsManager* physicsManager = nullptr;
    b2Body* body = nullptr;

    core::fs_float32 speed = 1.f;
    core::fs_float32 moving = 0.f;

    core::fs_float32 jumpForce = 1.f;
    bool jumping = false;

};

typedef std::unique_ptr<PlayerSceneNode> PlayerSceneNodePtr;
}

#endif //FIRESTORM_PLAYERSCENENODE_HPP
