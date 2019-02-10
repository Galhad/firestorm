


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

    void create(const Shader& vertexShader, const Shader& fragmentShader, const SwapChain& swapChain);
    virtual void destroy();

    const SwapChain* getSwapChain() const;
    const VkDescriptorPool& getDescriptorPool() const;
    const VkDescriptorSetLayout& getSceneDescriptorSetLayout() const;
    const VkDescriptorSetLayout& getMaterialDescriptorSetLayout() const;
    const RenderPass* getRenderPass() const;
    const VkPipeline& getGraphicsPipeline() const;
    const VkPipelineLayout& getGraphicsPipelineLayout() const;

private:
    RenderPassPtr renderPass;

    const SwapChain* swapChain = nullptr;

    VkPipelineLayout graphicsPipelineLayout = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline = VK_NULL_HANDLE;
    VkSampler textureSampler;

    VkDescriptorSetLayout sceneDescriptorSetLayout = VK_NULL_HANDLE;
    VkDescriptorSetLayout materialDescriptorSetLayout = VK_NULL_HANDLE;

    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;

private:
    void createDescriptorSetLayouts();
    void createPipelineLayout();
    void createPipeline(const Shader& vertexShader, const Shader& fragmentShader);
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
