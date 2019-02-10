


#ifndef FIRESTORM_ENGINECREATIONPARAMS_HPP
#define FIRESTORM_ENGINECREATIONPARAMS_HPP

#include "graphics/WindowCreationParams.hpp"
#include "graphics/GraphicsCreationParams.hpp"
#include "physics/PhysicsCreationParams.hpp"
#include "spdlog/spdlog.h"

namespace fs
{

struct EngineCreationParams
{
    graphics::WindowCreationParams windowCreationParams;
    graphics::GraphicsCreationParams graphicsCreationParams;
    physics::PhysicsCreationParams physicsCreationParams;

    spdlog::level::level_enum loggingLevel = spdlog::level::info;
};

}

#endif //FIRESTORM_ENGINECREATIONPARAMS_HPP
