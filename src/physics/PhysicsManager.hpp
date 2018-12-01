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

#ifndef FIRESTORM_PHYSICSMANAGER_HPP
#define FIRESTORM_PHYSICSMANAGER_HPP

#include "PhysicsCreationParams.hpp"

#include "Box2D/Box2D.h"

#include <memory>

namespace fs::physics
{
class PhysicsManager
{
public:
    PhysicsManager() = default;
    virtual ~PhysicsManager() = default;

    void create(const PhysicsCreationParams& creationParams);
    virtual void destroy();

//    virtual void updatePhysics(float deltaTime);
    void step(core::fs_int32 times = 1);

    const b2World* getWorld() const;

    core::fs_float32 getTimeStep() const;
    void setTimeStep(core::fs_float32 timeStep);

protected:
    std::unique_ptr<b2World> world = nullptr;

    core::fs_float32 timeStep;
    core::fs_int32 velocityIterations;
    core::fs_int32 positionIterations;

};

typedef std::unique_ptr<PhysicsManager> PhysicsManagerPtr;
}

#endif //FIRESTORM_PHYSICSMANAGER_HPP
