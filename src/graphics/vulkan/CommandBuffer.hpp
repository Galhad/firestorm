


#ifndef FIRESTORM_COMMANDBUFFER_HPP
#define FIRESTORM_COMMANDBUFFER_HPP

#include "Device.hpp"

#include <memory>

namespace fs::graphics
{
class CommandBuffer
{
public:
    CommandBuffer() = default;
    virtual ~CommandBuffer() = default;

    void create(const Device& device);
    virtual void destroy();

    void beginSingleTimeCommand();
    void endSingleTimeCommand();

    void reset();

    const VkCommandBuffer getCommandBuffer() const;

private:
    const Device* device = nullptr;

    VkCommandBuffer commandBuffer = VK_NULL_HANDLE;
};

typedef std::unique_ptr<CommandBuffer> CommandBufferPtr;

}
#endif //FIRESTORM_COMMANDBUFFER_HPP
