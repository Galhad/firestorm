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
    virtual void physicsUpdate();

protected:
    core::fs_float32 boundry = 0.7f;
    core::fs_float32 movementSpeed = 2.f;
    core::fs_float32 movementDirection = -1.f;
    core::Vector2f centerPostition = {};

    void setMovement(core::fs_float32 movement) const;
};

typedef std::unique_ptr<Slime> SlimePtr;
}

#endif //FIRESTORM_SLIME_HPP
