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

#ifndef FIRESTORM_SCENENODE_HPP
#define FIRESTORM_SCENENODE_HPP

#include "TransformationComponent.hpp"
#include "RendererComponent.hpp"
#include "BodyComponent.hpp"

#include "io/InputManager.hpp"
#include "physics/PhysicsManager.hpp"

#include <set>
#include <memory>

namespace fs::scene
{

class BodyComponent;

typedef std::unique_ptr<BodyComponent> BodyComponentPtr;

class SceneNode
{
public:
    SceneNode() = default;
    virtual ~SceneNode() = default;

    void create(io::InputManager& inputManager);
    virtual void destroy();

    virtual void update(float deltaTime);

    virtual void physicsUpdate();
    virtual void beginCollision(const BodyComponent& other);
    virtual void endCollision(const BodyComponent& other);

    const TransformationComponent& getTransformation() const;
    TransformationComponent& getTransformation();

    const RendererComponent* getRenderer() const;
    RendererComponent* getRenderer();

    const BodyComponent* getBody() const;
    BodyComponent* getBody();

    const std::set<std::string>& getLabels() const;
    std::set<std::string>& getLabels();
    void setLabels(const std::set<std::string>& labels);

protected:
    void createBodyComponent(physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                             const b2FixtureDef& fixtureDef);

protected:
    TransformationComponentPtr transformation = nullptr;
    RendererComponent* renderer = nullptr;
    BodyComponentPtr body = nullptr;

    io::InputManager* inputManager = nullptr;

    std::set<std::string> labels;
};

typedef std::unique_ptr<SceneNode> SceneNodePtr;
}

#endif //FIRESTORM_SCENENODE_HPP
