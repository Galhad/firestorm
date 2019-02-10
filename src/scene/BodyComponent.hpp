


#ifndef FIRESTORM_BODYCOMPONENT_HPP
#define FIRESTORM_BODYCOMPONENT_HPP

#include "Component.hpp"
#include "TransformationComponent.hpp"
#include "physics/PhysicsManager.hpp"
#include "SceneNode.hpp"

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

    void create(SceneNode& sceneNode, physics::PhysicsManager& physicsManager, const b2BodyDef& bodyDef,
                const b2FixtureDef& fixtureDef);
    void destroy() override;

    virtual void applyPhysicsStep();

    void beginCollision(const BodyComponent& other) const;
    void endCollision(const BodyComponent& other) const;

    void setBeginCollisionCallback(const CollisionCallback& beginCollisionCallback);
    void setEndCollisionCallback(const CollisionCallback& endCollisionCallback);

    b2Body* getBody();

protected:
    TransformationComponent* transformation = nullptr;

    physics::PhysicsManager* physicsManager = nullptr;
    b2Body* body = nullptr;

    const CollisionCallback* beginCollisionCallback = nullptr;
    const CollisionCallback* endCollisionCallback = nullptr;

};

typedef std::unique_ptr<BodyComponent> BodyComponentPtr;
}

#endif //FIRESTORM_BODYCOMPONENT_HPP
