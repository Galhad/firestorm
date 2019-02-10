


#ifndef FIRESTORM_PHYSICSCREATIONPARAMS_HPP
#define FIRESTORM_PHYSICSCREATIONPARAMS_HPP

#include "core/Types.hpp"

namespace fs::physics
{
struct PhysicsCreationParams
{
    core::Vector2f gravity = {0.f, 9.8f};
    core::fs_int32 velocityIterations = 8; // suggested by Box2D
    core::fs_int32 positionIterations = 3; // suggested by Box2D
    core::fs_float32 timeStep = 1.f / 60.f; // suggested by Box2D
};

}

#endif //FIRESTORM_PHYSICSCREATIONPARAMS_HPP
