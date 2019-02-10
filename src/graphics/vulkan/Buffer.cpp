


#include "Buffer.hpp"

namespace fs::graphics
{

void Buffer::create(const Device& device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                    void* data)
{
    this->device = &device;

    VkBufferCreateInfo bufferCreateInfo = {};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = size;
    bufferCreateInfo.usage = usage;
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device.getDevice(), &bufferCreateInfo, nullptr, &buffer) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create buffer!");
    }

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device.getDevice(), buffer, &memoryRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memoryRequirements.size;
    allocInfo.memoryTypeIndex = device.findMemoryType(memoryRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(device.getDevice(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate buffer memory!");
    }

    if (data != nullptr)
    {
        void* mappedData;
        vkMapMemory(device.getDevice(), bufferMemory, 0, size, 0, &mappedData);
        memcpy(mappedData, data, size);

        // If host coherency hasn't been requested, do a manual flush to make writes visible
        if ((properties & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0)
        {
            VkMappedMemoryRange mappedMemoryRange{};
            mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
            mappedMemoryRange.memory = bufferMemory;
            mappedMemoryRange.offset = 0;
            mappedMemoryRange.size = size;
            vkFlushMappedMemoryRanges(device.getDevice(), 1, &mappedMemoryRange);
        }
        vkUnmapMemory(device.getDevice(), bufferMemory);
    }

    vkBindBufferMemory(device.getDevice(), buffer, bufferMemory, 0);
}

void Buffer::destroy()
{
    if (buffer != VK_NULL_HANDLE)
    {
        vkDestroyBuffer(device->getDevice(), buffer, nullptr);
    }
    if (bufferMemory != VK_NULL_HANDLE)
    {
        vkFreeMemory(device->getDevice(), bufferMemory, nullptr);
    }

    device = nullptr;
}

const VkBuffer& Buffer::getBuffer() const
{
    return buffer;
}

const VkDeviceMemory& Buffer::getBufferMemory() const
{
    return bufferMemory;
}
}
