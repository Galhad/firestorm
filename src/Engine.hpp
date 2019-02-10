


#ifndef FIRESTORM_ENGINE_HPP
#define FIRESTORM_ENGINE_HPP

#include "EngineCreationParams.hpp"
#include "graphics/GraphicsManager.hpp"
#include "scene/SceneManager.hpp"
#include "physics/PhysicsManager.hpp"
#include "io/InputManager.hpp"
#include "io/FileProvider.hpp"
#include "utils/Logger.hpp"

#include <memory>
#include <functional>

namespace fs
{
class Engine
{
public:
    Engine();
    virtual ~Engine();

    void create(const EngineCreationParams& creationParams);
    virtual void destroy();

    void run();

    virtual void update(float deltaTime);

    graphics::GraphicsManager& getGraphicsManager() const;
    scene::SceneManager& getSceneManager() const;
    io::InputManager& getInputManager() const;
    io::FileProvider& getFileProvider() const;
    const utils::LoggerPtr& getLogger() const;

protected:
    virtual void render(const VkCommandBuffer& commandBuffer,
                        const VkPipelineLayout& pipelineLayout,
                        const VkDescriptorSet& uniformDescriptorSet);

protected:
    graphics::GraphicsManagerPtr graphicsManager;
    io::InputManagerPtr inputManager;
    io::FileProviderPtr fileProvider;
    scene::SceneManagerPtr sceneManager;
    physics::PhysicsManagerPtr physicsManager;

    utils::LoggerPtr logger = spdlog::stdout_color_mt(utils::CONSOLE_LOGGER_NAME);
};

typedef std::unique_ptr<Engine> EnginePtr;
}

#endif //FIRESTORM_ENGINE_HPP
