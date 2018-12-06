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

#ifndef FIRESTORM_BODYCOMPONENT_HPP
#define FIRESTORM_BODYCOMPONENT_HPP

#include "Component.hpp"
#include "TransformationComponent.hpp"

#include "Box2D/Box2D.h"

#include <memory>
#include <functional>

namespace fs::scene
{
class BodyComponent : public Component
{
public:
    using CollisionCallback = std::function<void(const BodyComponent& other)>;

public:
    BodyComponent() = default;
    ~BodyComponent() override = default;

    void create(TransformationComponent& transformation, b2Body& body);
    void destroy() override;

    virtual void applyPhysicsStep();

    void beginCollision(const BodyComponent& other) const;
    void endCollision(const BodyComponent& other) const;

    void setBeginCollisionCallback(const CollisionCallback& beginCollisionCallback);
    void setEndCollisionCallback(const CollisionCallback& endCollisionCallback);

    b2Body* getBody();

protected:
    TransformationComponent* transformation = nullptr;
    b2Body* body = nullptr;

    const CollisionCallback* beginCollisionCallback = nullptr;
    const CollisionCallback* endCollisionCallback = nullptr;

};

typedef std::unique_ptr<BodyComponent> BodyComponentPtr;
}

#endif //FIRESTORM_BODYCOMPONENT_HPP
