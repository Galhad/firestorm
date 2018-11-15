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

#ifndef FIRESTORM_GRAPHICSPIPELINE_HPP
#define FIRESTORM_GRAPHICSPIPELINE_HPP

#include "Shader.hpp"
#include "SwapChain.hpp"
#include "RenderPass.hpp"
#include "DepthImage.hpp"

#include <vulkan/vulkan.h>
#include <memory>

namespace fs::graphics
{
class GraphicsPipeline
{
public:
    GraphicsPipeline();
    virtual ~GraphicsPipeline() = default;

    void create(const Shader& vertexShader, const Shader& fragmentShader, const SwapChain& swapChain,
                const DepthImage& depthImage);
    virtual void destroy();

    const SwapChain* getSwapChain() const;
    const VkDescriptorPool& getDescriptorPool() const;
    const VkDescriptorSetLayout& getSceneDescriptorSetLayout() const;
    const VkDescriptorSetLayout& getMaterialDescriptorSetLayout() const;
    const std::vector<VkFramebuffer>& getFramebuffers() const;
    const RenderPass* getRenderPass() const;
    const VkPipeline& getGraphicsPipeline() const;
    const VkPipelineLayout& getGraphicsPipelineLayout() const;

private:
    RenderPassPtr renderPass;

    const SwapChain* swapChain = nullptr;
    const DepthImage* depthImage = nullptr;

    VkPipelineLayout graphicsPipelineLayout = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline = VK_NULL_HANDLE;
    VkSampler textureSampler;

    VkDescriptorSetLayout sceneDescriptorSetLayout = VK_NULL_HANDLE;
    VkDescriptorSetLayout materialDescriptorSetLayout = VK_NULL_HANDLE;

    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;

    std::vector<VkFramebuffer> framebuffers;

private:
    void createDescriptorSetLayouts();
    void createPipelineLayout();
    void createPipeline(const Shader& vertexShader, const Shader& fragmentShader);
    void createFramebuffers();
    void createTextureSampler();

    void createDescriptorPool();

    std::array<VkPipelineShaderStageCreateInfo, 2>
    getShaderStage(const Shader& vertexShader, const Shader& fragmentShader) const;
    VkPipelineVertexInputStateCreateInfo getVertexInput(VkVertexInputBindingDescription& bindingDescription,
                                                        std::array<VkVertexInputAttributeDescription, 3>& attributeDescription) const;
    VkPipelineInputAssemblyStateCreateInfo getInputAssembly() const;
    VkPipelineViewportStateCreateInfo getViewportState(VkViewport& viewport, VkRect2D& scissor) const;
    VkPipelineRasterizationStateCreateInfo getRasterization() const;
    VkPipelineMultisampleStateCreateInfo getMultisample() const;
    VkPipelineColorBlendAttachmentState getColorBlendAttachment() const;
    VkPipelineColorBlendStateCreateInfo getColorBlend(VkPipelineColorBlendAttachmentState& colorBlendAttachment) const;
    VkPipelineDepthStencilStateCreateInfo getDepthStencil() const;
    VkViewport getViewport() const;
    VkRect2D getScissors() const;
};

typedef std::unique_ptr<GraphicsPipeline> GraphicsPipelinePtr;

}

#endif //FIRESTORM_GRAPHICSPIPELINE_HPP
