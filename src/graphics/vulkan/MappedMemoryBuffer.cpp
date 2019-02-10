


#include "MappedMemoryBuffer.hpp"

namespace fs::graphics
{
void MappedMemoryBuffer::create(const fs::graphics::Device& device, VkDeviceSize size)
{
    Buffer::create(device, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    vkMapMemory(device.getDevice(), bufferMemory, 0, size, 0,
                &mappedData);
}

void MappedMemoryBuffer::destroy()
{
    vkUnmapMemory(device->getDevice(), bufferMemory);
    mappedData = nullptr;

    Buffer::destroy();
}

void* MappedMemoryBuffer::getMappedData() const
{
    return mappedData;
}
}
