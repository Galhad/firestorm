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

#include "SceneNode.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace fs::scene
{

void SceneNode::create(io::InputManager& inputManager)
{
    transformation = std::make_unique<TransformationComponent>();
    transformation->create(*this);
    renderer = nullptr;
    body = nullptr;
    scene = nullptr;

    SceneNode::inputManager = &inputManager;
}

void SceneNode::destroy()
{
    scene = nullptr;
    inputManager = nullptr;
    if (body != nullptr)
    {
        body->destroy();
        body = nullptr;
    }
    if (renderer != nullptr)
    {
        renderer->destroy();
        renderer = nullptr;
    }
    transformation->destroy();
    transformation = nullptr;
}

void SceneNode::update(float deltaTime)
{

}

const TransformationComponent& SceneNode::getTransformation() const
{
    return *transformation;
}

TransformationComponent& SceneNode::getTransformation()
{
    return *transformation;
}

const RendererComponent* SceneNode::getRenderer() const
{
    return renderer.get();
}

RendererComponent* SceneNode::getRenderer()
{
    return renderer.get();
}

const BodyComponent* SceneNode::getBody() const
{
    return body.get();
}

BodyComponent* SceneNode::getBody()
{
    return body.get();
}

void SceneNode::physicsUpdate()
{

}

const std::set<std::string>& SceneNode::getLabels() const
{
    return labels;
}

std::set<std::string>& SceneNode::getLabels()
{
    return labels;
}

void SceneNode::setLabels(const std::set<std::string>& labels)
{
    SceneNode::labels = labels;
}

void SceneNode::createBodyComponent(physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                                    const b2FixtureDef& fixtureDef)
{
    body = std::make_unique<BodyComponent>();
    body->create(*this, physicsManager, bodyDef, fixtureDef);
}

void SceneNode::beginCollision(const BodyComponent& other)
{

}

void SceneNode::endCollision(const BodyComponent& other)
{

}

io::InputManager* SceneNode::getInputManager() const
{
    return inputManager;
}

void SceneNode::applyPhysicsStep()
{
    if (body != nullptr)
    {
        body->applyPhysicsStep();
    }
}

Scene* SceneNode::getScene() const
{
    return scene;
}

void SceneNode::setScene(Scene* scene)
{
    SceneNode::scene = scene;
}

}
