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

#include "Engine.hpp"

#include <chrono>

namespace fs
{
Engine::Engine() : graphicsManager(new graphics::GraphicsManager()), inputManager(new io::InputManager()),
                   fileProvider(new io::FileProvider()), sceneManager(new scene::SceneManager()),
                   physicsManager(new physics::PhysicsManager())
{
}

Engine::~Engine()
{
    destroy();
}

void Engine::create(const EngineCreationParams& creationParams)
{
    logger->set_level(creationParams.loggingLevel);
    logger->info("Starting Firestorm engine");

    glfwInit();
    graphicsManager->create(creationParams.windowCreationParams, creationParams.graphicsCreationParams);
    graphicsManager->getVulkanDriver().setPerCommmandBufferCallback([&](const VkCommandBuffer& commandBuffer,
                                                                        const VkPipelineLayout& pipelineLayout,
                                                                        const VkDescriptorSet& uniformDescriptorSet)
                                                                    {
                                                                        render(commandBuffer, pipelineLayout,
                                                                               uniformDescriptorSet);
                                                                    });

    sceneManager->create();
    inputManager->create(graphicsManager->getWindow());
    fileProvider->create();

    graphicsManager->getWindow().setWindowResizedCallback([&](core::fs_int32 width, core::fs_int32 height)
                                                          {
                                                              graphicsManager->getVulkanDriver().recreateSwapChain();

                                                              const auto& activeScene = sceneManager->getActiveScene();
                                                              if (activeScene != nullptr)
                                                              {
                                                                  const auto& activeCamera = activeScene->getActiveCamera();
                                                                  if (activeCamera != nullptr)
                                                                  {
                                                                      activeCamera->updateUniformData();
                                                                  }
                                                              }
                                                          });

    physicsManager->create(creationParams.physicsCreationParams);
}

void Engine::destroy()
{
    physicsManager->destroy();
    fileProvider->destroy();
    inputManager->destroy();
    sceneManager->destroy();
    graphicsManager->destroy();

    glfwTerminate();
}

graphics::GraphicsManager& Engine::getGraphicsManager() const
{
    return *graphicsManager;
}

io::InputManager& Engine::getInputManager() const
{
    return *inputManager;
}

io::FileProvider& Engine::getFileProvider() const
{
    return *fileProvider;
}

void Engine::run()
{
    auto start = std::chrono::high_resolution_clock::now();

    float elapsedTime = 0.f;

    while (!glfwWindowShouldClose(graphicsManager->getWindow().getWindow()))
    {
        glfwPollEvents();
        auto end = std::chrono::high_resolution_clock::now();
        float deltaTime =
            static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())
            / 1'000'000'000.f;
        start = end;
        elapsedTime += deltaTime;

        update(deltaTime);

        const auto& activeScene = sceneManager->getActiveScene();

        auto steps = static_cast<core::fs_int32>(elapsedTime / physicsManager->getTimeStep());
        if (steps > 0)
        {
            if (activeScene != nullptr)
            {
                activeScene->physicsUpdate();
            }

//            logger->debug("Stepping physics {} times (1 steps = {}ms)", steps, physicsManager->getTimeStep());
            physicsManager->step(steps);
            elapsedTime -= physicsManager->getTimeStep() * steps;
        }

        if (activeScene != nullptr)
        {
            activeScene->update(deltaTime);
            activeScene->applyPhysicsStep();

            graphicsManager->draw();

            if (activeScene->isGeometryUpdated())
            {
                graphicsManager->getVulkanDriver().finish();
                graphicsManager->getVulkanDriver().recordCommandBuffers();
            }
        }

    }
    graphicsManager->getVulkanDriver().finish();
}

void Engine::render(const VkCommandBuffer& commandBuffer,
                    const VkPipelineLayout& pipelineLayout,
                    const VkDescriptorSet& uniformDescriptorSet)
{
    const auto& activeScene = sceneManager->getActiveScene();
    if (activeScene != nullptr)
    {
        activeScene->render(commandBuffer, pipelineLayout, uniformDescriptorSet);
    }
}

scene::SceneManager& Engine::getSceneManager() const
{
    return *sceneManager;
}

const utils::LoggerPtr& Engine::getLogger() const
{
    return logger;
}

}
