


#ifndef FIRESTORM_BUFFER_HPP
#define FIRESTORM_BUFFER_HPP

#include "Device.hpp"


#include <vulkan/vulkan.h>
#include <memory>

namespace fs::graphics
{
class Buffer
{
public:
    Buffer() = default;
    virtual ~Buffer() = default;

    void create(const Device& device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                void* data = nullptr);
    virtual void destroy();

    const VkBuffer& getBuffer() const;
    const VkDeviceMemory& getBufferMemory() const;

protected:
    const Device* device = nullptr;

    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory bufferMemory = VK_NULL_HANDLE;

};

typedef std::unique_ptr<Buffer> BufferPtr;
}

#endif //FIRESTORM_BUFFER_HPP
