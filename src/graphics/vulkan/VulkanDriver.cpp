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

#include "VulkanDriver.hpp"

#include "graphics/shaders/basic/BasicShaders.hpp"
#include "graphics/UniformData.hpp"
#include "CommandBuffer.hpp"

namespace fs::graphics
{

VulkanDriver::VulkanDriver() : instance(new Instance()), device(new Device()),
                               swapChain(new SwapChain()), vertexShader(new Shader()),
                               fragmentShader(new Shader()),
                               graphicsPipeline(new GraphicsPipeline()), depthImage(new DepthImage())
{

}

void VulkanDriver::create(const GraphicsCreationParams& graphicsCreationParams, Window& window)
{
    logger = spdlog::get(utils::CONSOLE_LOGGER_NAME);

    VulkanDriver::window = &window;

    instance->create(graphicsCreationParams.applicationName, graphicsCreationParams.applicationVersionMajor,
                     graphicsCreationParams.applicationVersionMinor,
                     graphicsCreationParams.applicationVersionPath,
                     graphicsCreationParams.enableValidationLayers);
    device->create(*instance, window);

    maxFramesInFlight = graphicsCreationParams.maxFramesInFlight;

    std::vector<core::fs_int8> vertexShaderCode(vert_spv, vert_spv + vert_spv_len);
    vertexShader->create(*device, vertexShaderCode, ShaderType::Vertex);

    std::vector<core::fs_int8> fragmentShaderCode(frag_spv, frag_spv + frag_spv_len);
    fragmentShader->create(*device, fragmentShaderCode, ShaderType::Fragment);

    createSwapChain();

    graphicsPipeline->create(*vertexShader, *fragmentShader, *swapChain);

    createBuffers();

    createSyncObjects();
}

void VulkanDriver::destroy()
{
    waitIdle();

    destroyVertexBuffers();

    destroySyncObjects();

    destroyBuffers();

    graphicsPipeline->destroy();

    destroySwapChain();

    fragmentShader->destroy();
    vertexShader->destroy();

    maxFramesInFlight = 0;

    device->destroy();
    instance->destroy();

    window = nullptr;
}

void VulkanDriver::createSwapChain()
{
    swapChain->create(*device);
    depthImage->create(*swapChain);
}

void VulkanDriver::destroySwapChain()
{
    depthImage->destroy();
    swapChain->destroy();
}

void VulkanDriver::recreateSwapChain()
{
    int width = 0;
    int height = 0;
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(window->getWindow(), &width, &height);
        glfwWaitEvents();
    }

    auto start = std::chrono::high_resolution_clock::now();
    waitIdle();

    swapChain->create(*device);
    depthImage->destroy();
    depthImage->create(*swapChain);

    destroyFramebuffers();
    createFramebuffers();

    destroyDrawCommandBuffers();
    createDrawCommandBuffers();
    recordCommandBuffers();

    waitIdle();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    logger->debug("Swapchain recreated in {}ms", durationMs);

}

void VulkanDriver::createSyncObjects()
{
    imageAvailableSemaphores.resize(maxFramesInFlight);
    renderFinishedSemaphores.resize(maxFramesInFlight);
    inFlightFences.resize(maxFramesInFlight);

    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceCreateInfo = {};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < maxFramesInFlight; ++i)
    {
        if (vkCreateSemaphore(device->getDevice(), &semaphoreCreateInfo, nullptr, &imageAvailableSemaphores[i]) !=
            VK_SUCCESS ||
            vkCreateSemaphore(device->getDevice(), &semaphoreCreateInfo, nullptr, &renderFinishedSemaphores[i]) !=
            VK_SUCCESS ||
            vkCreateFence(device->getDevice(), &fenceCreateInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create synchronization objects for a frame.");
        }
    }
}

void VulkanDriver::destroySyncObjects()
{
    for (int i = 0; i < maxFramesInFlight; ++i)
    {
        vkDestroySemaphore(device->getDevice(), renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(device->getDevice(), imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(device->getDevice(), inFlightFences[i], nullptr);
    }

    renderFinishedSemaphores.clear();
    imageAvailableSemaphores.clear();
    inFlightFences.clear();
}

void VulkanDriver::createUniformBuffers()
{
    uniformBuffer.create(*device, sizeof(UniformData));

    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = graphicsPipeline->getDescriptorPool();
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &graphicsPipeline->getSceneDescriptorSetLayout();

    if (vkAllocateDescriptorSets(device->getDevice(), &allocInfo, &uniformDescriptorSet) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate descriptor sets!");
    }


    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = uniformBuffer.getBuffer();
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformData);

    std::array<VkWriteDescriptorSet, 1> writeDescriptorSets = {};

    writeDescriptorSets[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSets[0].dstSet = uniformDescriptorSet;
    writeDescriptorSets[0].dstBinding = 0;
    writeDescriptorSets[0].dstArrayElement = 0;
    writeDescriptorSets[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writeDescriptorSets[0].descriptorCount = 1;
    writeDescriptorSets[0].pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(device->getDevice(), writeDescriptorSets.size(), writeDescriptorSets.data(), 0, nullptr);
}

void VulkanDriver::destroyUniformBuffers()
{
    uniformBuffer.destroy();
}

void VulkanDriver::createDrawCommandBuffers()
{
    commandBuffers.resize(framebuffers.size());

    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.commandPool = device->getCommandPool();
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if (vkAllocateCommandBuffers(device->getDevice(), &commandBufferAllocateInfo, commandBuffers.data()) !=
        VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocated command buffers.");
    }
}

void VulkanDriver::destroyDrawCommandBuffers()
{
    vkFreeCommandBuffers(device->getDevice(), device->getCommandPool(),
                         static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
}

void VulkanDriver::waitIdle()
{
    vkDeviceWaitIdle(device->getDevice());
}

void VulkanDriver::draw()
{
    vkWaitForFences(device->getDevice(), 1, &inFlightFences[currentFrame], VK_TRUE,
                    std::numeric_limits<uint64_t>::max());

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(device->getDevice(), swapChain->getSwapChain(),
                                            std::numeric_limits<uint64_t>::max(),
                                            imageAvailableSemaphores[currentFrame],
                                            VK_NULL_HANDLE, &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        recreateSwapChain();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::runtime_error("Failed to acquire swap chain image.");
    }

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(device->getDevice(), 1, &inFlightFences[currentFrame]);

    if (vkQueueSubmit(device->getGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to submit draw command buffer.");
    }

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapChain->getSwapChain()};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // optional

    result = vkQueuePresentKHR(device->getPresentationQueue(), &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        recreateSwapChain();
    }
    else if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to present swap chain image.");
    }

    currentFrame = (currentFrame + 1) % maxFramesInFlight;
}

void VulkanDriver::recordCommandBuffers()
{
    if (perCommmandBufferCallback == nullptr)
    {
        // Nothing to draw
        return;
    }

    std::array<VkClearValue, 2> clearValues = {};
    clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};

    VkRenderPassBeginInfo renderPassBeginInfo = {};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = graphicsPipeline->getRenderPass()->getRenderPass();
    renderPassBeginInfo.renderArea.offset = {0, 0};
    renderPassBeginInfo.renderArea.extent = swapChain->getSwapChainExtent();
    renderPassBeginInfo.clearValueCount = clearValues.size();
    renderPassBeginInfo.pClearValues = clearValues.data();

    for (size_t i = 0; i < commandBuffers.size(); ++i)
    {
        VkCommandBufferBeginInfo commandBufferBeginInfo = {};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        commandBufferBeginInfo.pInheritanceInfo = nullptr; // optional

        vkBeginCommandBuffer(commandBuffers[i], &commandBufferBeginInfo);

        renderPassBeginInfo.framebuffer = framebuffers[i];

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS,
                          graphicsPipeline->getGraphicsPipeline());

        VkViewport viewport{};
        viewport.width = swapChain->getSwapChainExtent().width;
        viewport.height = swapChain->getSwapChainExtent().height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffers[i], 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.extent.width = swapChain->getSwapChainExtent().width;
        scissor.extent.height = swapChain->getSwapChainExtent().height;
        scissor.offset.x = 0;
        scissor.offset.y = 0;
        vkCmdSetScissor(commandBuffers[i], 0, 1, &scissor);

        VkDeviceSize offsets[1] = {0};
        vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, &vertexBuffer.getBuffer(), offsets);
        vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer.getBuffer(), 0, VK_INDEX_TYPE_UINT32);


        perCommmandBufferCallback(commandBuffers[i], graphicsPipeline->getGraphicsPipelineLayout(),
                                  uniformDescriptorSet);

        vkCmdEndRenderPass(commandBuffers[i]);

        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to record command buffer.");
        }
    }
}

void VulkanDriver::finish()
{
    waitIdle();
}

const MappedMemoryBuffer& VulkanDriver::getUniformBuffer() const
{
    return uniformBuffer;
}

const Device& VulkanDriver::getDevice() const
{
    return *device;
}

const GraphicsPipeline& VulkanDriver::getGraphicsPipeline() const
{
    return *graphicsPipeline;
}

void VulkanDriver::createVertexBuffers(const std::vector<Vertex>& vertices, const std::vector<core::fs_uint32>& indices)
{
    destroyVertexBuffers();

    size_t vertexDataSize = vertices.size() * sizeof(graphics::Vertex);
    size_t indexDataSize = indices.size() * sizeof(core::fs_uint32);

    graphics::Buffer vertexStaging;
    vertexStaging.create(*device, static_cast<uint32_t>(vertexDataSize), VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                         (void*) vertices.data());

    vertexBuffer.create(*device, static_cast<uint32_t>(vertexDataSize),
                        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    graphics::Buffer indexStaging;
    indexStaging.create(*device, static_cast<uint32_t>(indexDataSize), VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                        (void*) indices.data());

    indexBuffer.create(*device, static_cast<uint32_t>(indexDataSize),
                       VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                       VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    CommandBuffer commandBuffer;
    commandBuffer.create(*device);
    commandBuffer.beginSingleTimeCommand();

    VkBufferCopy copyRegion = {};

    copyRegion.size = vertexDataSize;
    vkCmdCopyBuffer(
        commandBuffer.getCommandBuffer(),
        vertexStaging.getBuffer(),
        vertexBuffer.getBuffer(),
        1,
        &copyRegion);

    copyRegion.size = indexDataSize;
    vkCmdCopyBuffer(
        commandBuffer.getCommandBuffer(),
        indexStaging.getBuffer(),
        indexBuffer.getBuffer(),
        1,
        &copyRegion);

    commandBuffer.endSingleTimeCommand();

    vertexStaging.destroy();
    indexStaging.destroy();

    recordCommandBuffers();
}

void VulkanDriver::destroyVertexBuffers()
{
    vertexBuffer.destroy();
    indexBuffer.destroy();
}

const VulkanDriver::CommandBufferCallback& VulkanDriver::getPerCommmandBufferCallback() const
{
    return perCommmandBufferCallback;
}

void VulkanDriver::setPerCommmandBufferCallback(const CommandBufferCallback& callback)
{
    perCommmandBufferCallback = callback;
}

void VulkanDriver::createFramebuffers()
{
    const auto& swapChainImageViews = swapChain->getSwapChainImageViews();
    framebuffers.resize(swapChainImageViews.size());

    for (size_t i = 0; i < swapChainImageViews.size(); ++i)
    {
        std::array<VkImageView, 2> attachments = {
            swapChainImageViews[i],
            depthImage->getImageView()
        };

        VkFramebufferCreateInfo framebufferCreateInfo = {};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.renderPass = graphicsPipeline->getRenderPass()->getRenderPass();
        framebufferCreateInfo.attachmentCount = attachments.size();
        framebufferCreateInfo.pAttachments = attachments.data();
        framebufferCreateInfo.width = swapChain->getSwapChainExtent().width;
        framebufferCreateInfo.height = swapChain->getSwapChainExtent().height;
        framebufferCreateInfo.layers = 1;

        if (vkCreateFramebuffer(swapChain->getDevice()->getDevice(), &framebufferCreateInfo, nullptr,
                                &framebuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create framebuffer.");
        }
    }
}

void VulkanDriver::destroyFramebuffers()
{
    for (const auto& framebuffer : framebuffers)
    {
        vkDestroyFramebuffer(device->getDevice(), framebuffer, nullptr);
    }
}

void VulkanDriver::createBuffers()
{
    createFramebuffers();
    createUniformBuffers();
    createDrawCommandBuffers();
}

void VulkanDriver::destroyBuffers()
{
    destroyDrawCommandBuffers();
    destroyUniformBuffers();
    destroyFramebuffers();
}

}
