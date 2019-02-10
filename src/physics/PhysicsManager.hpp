


#ifndef FIRESTORM_PHYSICSMANAGER_HPP
#define FIRESTORM_PHYSICSMANAGER_HPP

#include "Box2D/Box2D.h"

#include "PhysicsCreationParams.hpp"

#include <memory>

namespace fs::physics
{
class PhysicsManager : public b2ContactListener
{
public:
    PhysicsManager() = default;
    ~PhysicsManager() override = default;

    void create(const PhysicsCreationParams& creationParams);
    virtual void destroy();

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

    void step(core::fs_int32 times = 1);

    const b2World* getWorld() const;
    b2World* getWorld();

    core::fs_float32 getTimeStep() const;
    void setTimeStep(core::fs_float32 timeStep);

protected:
    std::unique_ptr<b2World> world = nullptr;

    core::fs_float32 timeStep = 1.f / 60.f;
    core::fs_int32 velocityIterations = 9;
    core::fs_int32 positionIterations = 3;

};

typedef std::unique_ptr<PhysicsManager> PhysicsManagerPtr;
}

#endif //FIRESTORM_PHYSICSMANAGER_HPP
