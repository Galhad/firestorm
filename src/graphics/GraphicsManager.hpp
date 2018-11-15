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

    Texture* createTexture(const io::Resource& resource, core::fs_uint32 pixelsPerUnit = 100) const;

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
