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

#ifndef FIRESTORM_VULKANDRIVER_HPP
#define FIRESTORM_VULKANDRIVER_HPP


#include "graphics/GraphicsCreationParams.hpp"

#include "Instance.hpp"
#include "Device.hpp"
#include "SwapChain.hpp"
#include "DepthImage.hpp"
#include "GraphicsPipeline.hpp"
#include "MappedMemoryBuffer.hpp"
#include "Vertex.hpp"
#include "utils/Logger.hpp"

#include <memory>
#include <functional>

namespace fs::graphics
{
class VulkanDriver
{
public:
    using CommandBufferCallback = std::function<void(const VkCommandBuffer& commandBuffer,
                                                     const VkPipelineLayout& pipelineLayout,
                                                     const VkDescriptorSet& uniformDescriptorSet)>;
public:
    VulkanDriver();
    virtual ~VulkanDriver() = default;

    void create(const GraphicsCreationParams& graphicsCreationParams, Window& window);
    virtual void destroy();

    void draw();
    void recordCommandBuffers();
    void finish();

    void recreateSwapChain();

    void createVertexBuffers(const std::vector<Vertex>& vertices, const std::vector<core::fs_uint32>& indices);

    const MappedMemoryBuffer& getUniformBuffer() const;
    const Device& getDevice() const;
    const GraphicsPipeline& getGraphicsPipeline() const;

    const CommandBufferCallback& getPerCommmandBufferCallback() const;
    void setPerCommmandBufferCallback(const CommandBufferCallback& callback);

private:
    void createSwapChain();
    void destroySwapChain();

    void createSyncObjects();
    void destroySyncObjects();

    void createFramebuffers();
    void destroyFramebuffers();

    void createUniformBuffers();
    void destroyUniformBuffers();

    void createDrawCommandBuffers();
    void destroyDrawCommandBuffers();

    void destroyVertexBuffers();

    void createBuffers();
    void destroyBuffers();

    void waitIdle();

private:
    utils::LoggerPtr logger;

    const Window* window = nullptr;

    InstancePtr instance;
    DevicePtr device;
    SwapChainPtr swapChain;
    DepthImagePtr depthImage;
    GraphicsPipelinePtr graphicsPipeline;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    core::fs_uint32 currentFrame = 0;
    core::fs_uint8 maxFramesInFlight;

    std::vector<VkFramebuffer> framebuffers;

    MappedMemoryBuffer uniformBuffer;
    VkDescriptorSet uniformDescriptorSet;

    std::vector<VkCommandBuffer> commandBuffers;

    Buffer vertexBuffer;
    Buffer indexBuffer;

    ShaderPtr vertexShader;
    ShaderPtr fragmentShader;

    CommandBufferCallback perCommmandBufferCallback = {};
};

typedef std::unique_ptr<VulkanDriver> VulkanDriverPtr;
}

#endif //FIRESTORM_VULKANDRIVER_HPP
