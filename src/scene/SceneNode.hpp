


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

class Scene;

class SceneNode
{
public:
    SceneNode() = default;
    virtual ~SceneNode() = default;

    void create(io::InputManager& inputManager);
    virtual void destroy();

    virtual void update(float deltaTime);

    virtual void physicsUpdate();
    virtual void applyPhysicsStep();
    virtual void beginCollision(const BodyComponent& other);
    virtual void endCollision(const BodyComponent& other);

    const TransformationComponent& getTransformation() const;
    TransformationComponent& getTransformation();

    const RendererComponent* getRenderer() const;
    RendererComponent* getRenderer();

    const BodyComponent* getBody() const;
    BodyComponent* getBody();

    io::InputManager* getInputManager() const;

    const std::set<std::string>& getLabels() const;
    std::set<std::string>& getLabels();
    void setLabels(const std::set<std::string>& labels);

    Scene* getScene() const;
    void setScene(Scene* scene);

protected:
    void createBodyComponent(physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                             const b2FixtureDef& fixtureDef);

protected:
    Scene* scene = nullptr;

    TransformationComponentPtr transformation = nullptr;
    RendererComponentPtr renderer = nullptr;
    BodyComponentPtr body = nullptr;

    io::InputManager* inputManager = nullptr;

    std::set<std::string> labels;
};

typedef std::unique_ptr<SceneNode> SceneNodePtr;
}

#endif //FIRESTORM_SCENENODE_HPP
