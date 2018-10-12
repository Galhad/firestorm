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

#include "GraphicsManager.hpp"

#include "shaders/basic/BasicShaders.hpp"

#include <vector>

namespace fs::graphics
{
GraphicsManager::GraphicsManager() : window(new Window()), vulkanInstance(new Instance()),
                                     vulkanDevice(new Device()), vulkanSwapChain(new SwapChain()),
                                     vulkanVertexShader(new Shader()), vulkanFragmentShader(new Shader()),
                                     vulkanGraphicsPipeline(new GraphicsPipeline()), vulkanDepthImage(new DepthImage())
{

}

void GraphicsManager::create(const WindowCreationParams& windowCreationParams,
                             const GraphicsCreationParams& graphicsCreationParams)
{
    window->create(windowCreationParams.windowSize, windowCreationParams.windowTitle, windowCreationParams.windowFlags);
    vulkanInstance->create(graphicsCreationParams.applicationName, graphicsCreationParams.applicationVersionMajor,
                           graphicsCreationParams.applicationVersionMinor,
                           graphicsCreationParams.applicationVersionPath,
                           graphicsCreationParams.enableValidationLayers);
    vulkanDevice->create(*vulkanInstance, *window);

    createSwapChain();
}

void GraphicsManager::createSwapChain() const
{
    vulkanSwapChain->create(*vulkanDevice);

    std::vector<core::fs_int8> vertexShaderCode(vert_spv, vert_spv + vert_spv_len);
    vulkanVertexShader->create(*vulkanDevice, vertexShaderCode, ShaderType::Vertex);

    std::vector<core::fs_int8> fragmentShaderCode(frag_spv, frag_spv + frag_spv_len);
    vulkanFragmentShader->create(*vulkanDevice, fragmentShaderCode, ShaderType::Fragment);

    vulkanDepthImage->create(*vulkanSwapChain);

    vulkanGraphicsPipeline->create(*vulkanVertexShader, *vulkanFragmentShader, *vulkanSwapChain, *vulkanDepthImage);
}

void GraphicsManager::destroy()
{
    destroySwapChain();

    vulkanDevice->destroy();
    vulkanInstance->destroy();
    window->destroy();
}

void GraphicsManager::destroySwapChain() const
{
    vulkanGraphicsPipeline->destroy();

    vulkanDepthImage->destroy();

    vulkanFragmentShader->destroy();
    vulkanVertexShader->destroy();

    vulkanSwapChain->destroy();
}

const Window& GraphicsManager::getWindow() const
{
    return *window;
}

void GraphicsManager::recreateSwapChain()
{
    int width = 0;
    int height = 0;
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(window->getWindow(), &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(vulkanDevice->getDevice());

    destroySwapChain();
    createSwapChain();
}

}
