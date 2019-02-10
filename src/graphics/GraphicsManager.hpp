


#ifndef FIRESTORM_GRAPHICSMANAGER_HPP
#define FIRESTORM_GRAPHICSMANAGER_HPP


#include "vulkan/Instance.hpp"
#include "vulkan/Device.hpp"
#include "vulkan/SwapChain.hpp"
#include "vulkan/Shader.hpp"
#include "vulkan/GraphicsPipeline.hpp"
#include "vulkan/DepthImage.hpp"
#include "vulkan/VulkanDriver.hpp"

#include "Window.hpp"
#include "WindowCreationParams.hpp"
#include "GraphicsCreationParams.hpp"
#include "Texture.hpp"
#include "UniformData.hpp"
#include "SpriteSheet.hpp"

#include "io/Resource.hpp"
#include "scene/Scene.hpp"

#include <list>
#include <memory>

namespace fs::graphics
{
class GraphicsManager
{
public:
    GraphicsManager();
    virtual ~GraphicsManager() = default;

    void create(const WindowCreationParams& windowCreationParams, const GraphicsCreationParams& graphicsCreationParams);
    virtual void destroy();

    void draw();

    SpriteSheet* createSpriteSheet(const io::Resource& resource, core::fs_uint32 pixelsPerUnit = 100);
    void clearSpriteSheets();

    const graphics::Window& getWindow() const;
    graphics::Window& getWindow();

    const VulkanDriver& getVulkanDriver() const;
    VulkanDriver& getVulkanDriver();

    const std::list<SpriteSheet>& getSpriteSheets() const;

protected:
    void createVertexBuffers();

protected:
    WindowPtr window;
    VulkanDriverPtr vulkanDriver;

    std::list<SpriteSheet> spriteSheets;
};

typedef std::unique_ptr<GraphicsManager> GraphicsManagerPtr;

}

#endif //FIRESTORM_GRAPHICSMANAGER_HPP
