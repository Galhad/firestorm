


#include "CommandBuffer.hpp"

namespace fs::graphics
{

void CommandBuffer::create(const Device& device)
{
    this->device = &device;

    VkCommandBufferAllocateInfo allocateInfo = {};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocateInfo.commandPool = device.getCommandPool();
    allocateInfo.commandBufferCount = 1;

    vkAllocateCommandBuffers(device.getDevice(), &allocateInfo, &commandBuffer);
}

void CommandBuffer::destroy()
{
    vkFreeCommandBuffers(device->getDevice(), device->getCommandPool(), 1, &commandBuffer);
    commandBuffer = VK_NULL_HANDLE;

    device = nullptr;
}

void CommandBuffer::beginSingleTimeCommand()
{
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);
}

void CommandBuffer::endSingleTimeCommand()
{
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(device->getGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(device->getGraphicsQueue());
}

const VkCommandBuffer CommandBuffer::getCommandBuffer() const
{
    return commandBuffer;
}

void CommandBuffer::reset()
{
    vkResetCommandBuffer(commandBuffer, 0);
}

}
