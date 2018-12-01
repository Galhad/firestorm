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

#include "PhysicsManager.hpp"

namespace fs::physics
{

void PhysicsManager::create(const PhysicsCreationParams& creationParams)
{
    world = std::make_unique<b2World>(b2Vec2(creationParams.gravity.x, creationParams.gravity.y));

    timeStep = creationParams.timeStep;
    velocityIterations = creationParams.velocityIterations;
    positionIterations = creationParams.positionIterations;
}

void PhysicsManager::destroy()
{
    velocityIterations = 0;
    positionIterations = 0;
    timeStep = 0;

    world = nullptr;
}

//void PhysicsManager::updatePhysics(float deltaTime)
//{
//
//}

void PhysicsManager::step(core::fs_int32 times)
{
    world->Step(timeStep * times, velocityIterations, positionIterations);
}

const b2World* PhysicsManager::getWorld() const
{
    return world.get();
}


core::fs_float32 PhysicsManager::getTimeStep() const
{
    return timeStep;
}

void PhysicsManager::setTimeStep(core::fs_float32 timeStep)
{
    PhysicsManager::timeStep = timeStep;
}

}
