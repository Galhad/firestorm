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

#include "Enemy.hpp"
#include "Labels.hpp"

namespace fs::scene
{

void Enemy::create(io::InputManager& inputManager, physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                   const b2FixtureDef& fixtureDef, const Animation& walkingAnimation)
{
    AnimatedSpriteSceneNode::create(inputManager, walkingAnimation);

    logger = spdlog::get(utils::CONSOLE_LOGGER_NAME);

    Enemy::walkingAnimation = walkingAnimation;

    createBodyComponent(physicsManager, bodyDef, fixtureDef);

    transformation->setLayer(0.1f);

    labels.insert(LABEL_ENEMY);
}

void Enemy::destroy()
{
    AnimatedSpriteSceneNode::destroy();
}

const core::Vector2f& Enemy::getStartingPosition() const
{
    return startingPosition;
}

void Enemy::setStartingPosition(const core::Vector2f& startingPosition)
{
    Enemy::startingPosition = startingPosition;
}
}
