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

#include "GraphicsPipeline.hpp"

#include "Vertex.hpp"
#include "graphics/Transform.hpp"

namespace fs::graphics
{

GraphicsPipeline::GraphicsPipeline() : renderPass(new RenderPass())
{

}

void GraphicsPipeline::create(const Shader& vertexShader, const Shader& fragmentShader, const SwapChain& swapChain)
{
    this->swapChain = &swapChain;

    renderPass->create(swapChain);

    createDescriptorSetLayouts();

    createPipelineLayout();
    createPipeline(vertexShader, fragmentShader);

    createTextureSampler();

    createDescriptorPool();
}

void GraphicsPipeline::destroy()
{
    vkDestroyDescriptorPool(swapChain->getDevice()->getDevice(), descriptorPool, nullptr);

    vkDestroySampler(swapChain->getDevice()->getDevice(), textureSampler, nullptr);

    vkDestroyPipeline(swapChain->getDevice()->getDevice(), graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(swapChain->getDevice()->getDevice(), graphicsPipelineLayout, nullptr);

    vkDestroyDescriptorSetLayout(swapChain->getDevice()->getDevice(), sceneDescriptorSetLayout, nullptr);
    vkDestroyDescriptorSetLayout(swapChain->getDevice()->getDevice(), materialDescriptorSetLayout, nullptr);

    renderPass->destroy();

    swapChain = nullptr;
}

void
GraphicsPipeline::createPipeline(const Shader& vertexShader, const Shader& fragmentShader)
{
    std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages = getShaderStage(vertexShader, fragmentShader);

    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescription = Vertex::getAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInput = getVertexInput(bindingDescription, attributeDescription);
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = getInputAssembly();

    VkViewport viewport = getViewport();
    VkRect2D scissor = getScissors();
    VkPipelineViewportStateCreateInfo viewportState = getViewportState(viewport, scissor);
    VkPipelineRasterizationStateCreateInfo rasterization = getRasterization();
    VkPipelineMultisampleStateCreateInfo multisample = getMultisample();

    VkPipelineColorBlendAttachmentState colorBlendAttachment = getColorBlendAttachment();
    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = getColorBlend(colorBlendAttachment);

    VkPipelineDepthStencilStateCreateInfo depthStencil = getDepthStencil();

    VkDynamicState dynamicStates[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };

    VkPipelineDynamicStateCreateInfo dynamicState = {};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = 2;
    dynamicState.pDynamicStates = dynamicStates;

    VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {};
    graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    // shaders
    graphicsPipelineCreateInfo.stageCount = 2;
    graphicsPipelineCreateInfo.pStages = shaderStages.data();
    // fixed functions
    graphicsPipelineCreateInfo.pVertexInputState = &vertexInput;
    graphicsPipelineCreateInfo.pInputAssemblyState = &inputAssembly;
    graphicsPipelineCreateInfo.pViewportState = &viewportState;
    graphicsPipelineCreateInfo.pRasterizationState = &rasterization;
    graphicsPipelineCreateInfo.pMultisampleState = &multisample;
    graphicsPipelineCreateInfo.pDepthStencilState = &depthStencil; // optional
    graphicsPipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo;
    graphicsPipelineCreateInfo.pDynamicState = &dynamicState; // optional
    // graphicsPipeline layout
    graphicsPipelineCreateInfo.layout = graphicsPipelineLayout;
    // render passes
    graphicsPipelineCreateInfo.renderPass = renderPass->getRenderPass();
    graphicsPipelineCreateInfo.subpass = 0; // index
    // base
    graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE; // optional
    graphicsPipelineCreateInfo.basePipelineIndex = -1; // optional

    if (vkCreateGraphicsPipelines(swapChain->getDevice()->getDevice(), VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo,
                                  nullptr, &graphicsPipeline) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create graphics graphicsPipeline.");
    }
}

VkPipelineDepthStencilStateCreateInfo GraphicsPipeline::getDepthStencil() const
{
    VkPipelineDepthStencilStateCreateInfo depthStencil = {};
    depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.depthTestEnable = VK_TRUE;
    depthStencil.depthWriteEnable = VK_TRUE;
    depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
    depthStencil.depthBoundsTestEnable = VK_FALSE;
    depthStencil.minDepthBounds = 0.0f; // Optional
    depthStencil.maxDepthBounds = 1.0f; // Optional
    depthStencil.stencilTestEnable = VK_FALSE;
    depthStencil.front = {}; // Optional
    depthStencil.back = {}; // Optional

    return depthStencil;
}

VkPipelineColorBlendStateCreateInfo
GraphicsPipeline::getColorBlend(VkPipelineColorBlendAttachmentState& colorBlendAttachment) const
{
    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = {};
    colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
    colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
    colorBlendStateCreateInfo.attachmentCount = 1;
    colorBlendStateCreateInfo.pAttachments = &colorBlendAttachment;
    colorBlendStateCreateInfo.blendConstants[0] = 0.0f; // optional
    colorBlendStateCreateInfo.blendConstants[1] = 0.0f; // optional
    colorBlendStateCreateInfo.blendConstants[2] = 0.0f; // optional
    colorBlendStateCreateInfo.blendConstants[3] = 0.0f; // optional


    return colorBlendStateCreateInfo;
}

VkPipelineColorBlendAttachmentState GraphicsPipeline::getColorBlendAttachment() const
{
    VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};
    colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
                                               | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    // for alpha blending
    // finalColor.rgb = newAlpha * newColor + (1 - newAlpha) * oldColor;
    // finalColor.a = newAlpha.a;
    colorBlendAttachmentState.blendEnable = VK_TRUE;
    colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

    return colorBlendAttachmentState;
}

VkPipelineMultisampleStateCreateInfo GraphicsPipeline::getMultisample() const
{
    // multisampling AA requires gpu feature
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
    multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
    multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampleStateCreateInfo.minSampleShading = 1.0f; // optional
    multisampleStateCreateInfo.pSampleMask = nullptr; // optional
    multisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE; // optional
    multisampleStateCreateInfo.alphaToOneEnable = VK_FALSE; // optional

    return multisampleStateCreateInfo;
}

VkPipelineRasterizationStateCreateInfo GraphicsPipeline::getRasterization() const
{
    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
    rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    // depth clamp requires gpu feature
    rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
    rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    // modes other than fill requires gpu feature
    rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationStateCreateInfo.lineWidth = 1.0f;
    rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
    rasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f; // optional
    rasterizationStateCreateInfo.depthBiasClamp = 0.0f; // optional
    rasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f; // optional

    return rasterizationStateCreateInfo;
}

VkPipelineViewportStateCreateInfo GraphicsPipeline::getViewportState(VkViewport& viewport, VkRect2D& scissor) const
{
    // multiple viewpors and scissors requires gpu feature
    VkPipelineViewportStateCreateInfo viewportStateCreateInfo = {};
    viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateCreateInfo.viewportCount = 1;
    viewportStateCreateInfo.pViewports = &viewport;
    viewportStateCreateInfo.scissorCount = 1;
    viewportStateCreateInfo.pScissors = &scissor;
    return viewportStateCreateInfo;
}

VkRect2D GraphicsPipeline::getScissors() const
{
    VkRect2D scissor = {};
    scissor.offset = {0, 0};
    scissor.extent = swapChain->getSwapChainExtent();
    return scissor;
}

VkViewport GraphicsPipeline::getViewport() const
{
    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = swapChain->getSwapChainExtent().width;
    viewport.height = swapChain->getSwapChainExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    return viewport;
}

VkPipelineInputAssemblyStateCreateInfo GraphicsPipeline::getInputAssembly() const
{
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
    inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;
    return inputAssemblyStateCreateInfo;
}

VkPipelineVertexInputStateCreateInfo
GraphicsPipeline::getVertexInput(VkVertexInputBindingDescription& bindingDescription,
                                 std::array<VkVertexInputAttributeDescription, 3>& attributeDescription) const
{
    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
    vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
    vertexInputStateCreateInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescription.size());
    vertexInputStateCreateInfo.pVertexAttributeDescriptions = attributeDescription.data();
    return vertexInputStateCreateInfo;
}

std::array<VkPipelineShaderStageCreateInfo, 2>
GraphicsPipeline::getShaderStage(const Shader& vertexShader, const Shader& fragmentShader) const
{
    VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertexShader.getShaderModule();
    vertShaderStageInfo.pName = "main";
    // pSpecializationInfo allows to set shader's constants
    vertShaderStageInfo.pSpecializationInfo = nullptr;

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragmentShader.getShaderModule();
    fragShaderStageInfo.pName = "main";
    // pSpecializationInfo allows to set shader's constants
    fragShaderStageInfo.pSpecializationInfo = nullptr;

    return {vertShaderStageInfo, fragShaderStageInfo};
}

void GraphicsPipeline::createPipelineLayout()
{
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
    pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    std::array<VkDescriptorSetLayout, 2> descriptorSetLayouts = {sceneDescriptorSetLayout, materialDescriptorSetLayout};
    pipelineLayoutCreateInfo.pSetLayouts = descriptorSetLayouts.data();
    pipelineLayoutCreateInfo.setLayoutCount = descriptorSetLayouts.size();

    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(Transform);

    pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
    pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;

    if (vkCreatePipelineLayout(swapChain->getDevice()->getDevice(), &pipelineLayoutCreateInfo, nullptr,
                               &graphicsPipelineLayout) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create graphicsPipeline layout!");
    }
}

void GraphicsPipeline::createTextureSampler()
{
    VkSamplerCreateInfo samplerInfo = {};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = 16;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;

    if (vkCreateSampler(swapChain->getDevice()->getDevice(), &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create texture sampler!");
    }
}

void GraphicsPipeline::createDescriptorPool()
{
    core::fs_uint32 max = 10;
    std::array<VkDescriptorPoolSize, 2> poolSizes = {};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = max;
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = max;

    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = poolSizes.size();
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = max + 1;

    if (vkCreateDescriptorPool(swapChain->getDevice()->getDevice(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create descriptor pool!");
    }
}

const SwapChain* GraphicsPipeline::getSwapChain() const
{
    return swapChain;
}

const VkDescriptorPool& GraphicsPipeline::getDescriptorPool() const
{
    return descriptorPool;
}

const RenderPass* GraphicsPipeline::getRenderPass() const
{
    return renderPass.get();
}

const VkPipeline& GraphicsPipeline::getGraphicsPipeline() const
{
    return graphicsPipeline;
}

const VkPipelineLayout& GraphicsPipeline::getGraphicsPipelineLayout() const
{
    return graphicsPipelineLayout;
}

void GraphicsPipeline::createDescriptorSetLayouts()
{

    std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings;

    // Set 0: Scene matrices
    VkDescriptorSetLayoutBinding uboLayoutBinding = {};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    setLayoutBindings.push_back(uboLayoutBinding);

    VkDescriptorSetLayoutCreateInfo descriptorLayout = {};
    descriptorLayout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorLayout.bindingCount = static_cast<uint32_t>(setLayoutBindings.size());
    descriptorLayout.pBindings = setLayoutBindings.data();

    if (vkCreateDescriptorSetLayout(swapChain->getDevice()->getDevice(), &descriptorLayout, nullptr,
                                    &sceneDescriptorSetLayout) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create scene descriptor set layout!");
    }

    setLayoutBindings.clear();
    VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
    samplerLayoutBinding.binding = 0;
    samplerLayoutBinding.descriptorCount = 1;
    samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerLayoutBinding.pImmutableSamplers = nullptr;
    samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    setLayoutBindings.push_back(samplerLayoutBinding);
    if (vkCreateDescriptorSetLayout(swapChain->getDevice()->getDevice(), &descriptorLayout, nullptr,
                                    &materialDescriptorSetLayout) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create material descriptor set layout!");
    }
}

const VkDescriptorSetLayout& GraphicsPipeline::getSceneDescriptorSetLayout() const
{
    return sceneDescriptorSetLayout;
}

const VkDescriptorSetLayout& GraphicsPipeline::getMaterialDescriptorSetLayout() const
{
    return materialDescriptorSetLayout;
}

}
