


#include "CommandPool.hpp"

namespace fs::graphics
{

void CommandPool::create(VkDevice device, const core::fs_uint32 queueFamilyIndex)
{
    this->device = device;

    VkCommandPoolCreateInfo commandPoolCreateInfo = {};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;
    commandPoolCreateInfo.flags = 0; // optional

    if (vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &commandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create command pool.");
    }
}

void CommandPool::destroy()
{
    vkDestroyCommandPool(device, commandPool, nullptr);
}

const VkCommandPool CommandPool::getCommandPool() const
{
    return commandPool;
}

}
