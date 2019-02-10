


#include "SceneNode.hpp"

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
